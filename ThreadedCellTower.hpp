#ifndef THREADEDCELLTOWER_HPP
#define THREADEDCELLTOWER_HPP

#include <thread>
#include <mutex>
#include "CellTower.hpp"
#include "Basicio.h"
#include "BasicException.hpp"

class ThreadedCellTower : public CellTower {
public:
    ~ThreadedCellTower() override {
        for (unsigned long i = 0; i < workerThreads.size(); ++i) {
            if (workerThreads[i]->joinable()) workerThreads[i]->join();
            delete workerThreads[i];
        }
    }

    // --- THIS IS THE MISSING FUNCTION ---
    void simulateWithLoadedUsers(const Vector<UserDevice>& users) {
        IO::printLine("Mapping loaded users to frequency channels...");
        
        int numChannels = (int)(totalBandwidthKHz / channelWidthKHz);
        channels.clear();
        
        // 1. Initialize Channels
        for(int i=0; i<numChannels; ++i) {
            FrequencyChannel<UserDevice> ch(usersPerChannel);
            channels.push_back(ch);
        }

        // 2. Distribute Users
        int accepted = 0;
        int dropped = 0;

        for(unsigned long i=0; i<users.size(); ++i) {
            // Calculate which channel this user belongs to
            int channelIndex = (i / usersPerChannel);
            
            // Handle antenna reuse (parallel capacity)
            int effectiveChannel = channelIndex % numChannels;
            
            // Check absolute capacity limits
            if (channelIndex >= (numChannels * antennaCount)) {
                dropped++;
                continue;
            }

            // Attempt to add user
            if(channels[effectiveChannel].addUser(users[i])) {
                accepted++;
            } else {
                dropped++;
            }
        }
        
        // 3. Print Results
        IO::print("Simulation Result: Accepted ");
        IO::printInt(accepted);
        IO::print(" users. Dropped ");
        IO::printInt(dropped);
        IO::printLine(" users (Capacity Full).");
        
        // 4. Calculate Core Overhead
        long totalMsgs = accepted * msgPerUser;
        IO::print("Core Overhead Generated: ");
        IO::printFloat(core.calculateOverhead(totalMsgs));
        IO::printLine(" units.");
    }

protected:
    Vector<std::thread*> workerThreads;
    std::mutex channelMutex;

    // Legacy method for random simulation (required by ThreadedTowers.hpp classes)
    void simulateConcurrentUsers(int numChannels, int usersPerChannel, int idStart) {
        channels.clear();
        for (int i = 0; i < numChannels; ++i) {
            FrequencyChannel<UserDevice> channel(usersPerChannel);
            channels.push_back(channel);
        }

        for (int i = 0; i < numChannels; ++i) {
            workerThreads.push_back(new std::thread([this, i, usersPerChannel, idStart]() {
                try {
                    for (int j = 0; j < usersPerChannel; ++j) {
                        UserDevice user(idStart + i * usersPerChannel + j);
                        safeAddUserToChannel(channels[i], user);
                    }
                } catch (...) {}
            }));
        }
        
        for (unsigned long i = 0; i < workerThreads.size(); ++i) {
            if (workerThreads[i]->joinable()) workerThreads[i]->join();
            delete workerThreads[i];
        }
        workerThreads.clear();
    }

    bool safeAddUserToChannel(FrequencyChannel<UserDevice>& channel, const UserDevice& user) {
        std::lock_guard<std::mutex> lock(channelMutex);
        return channel.addUser(user);
    }
};

#endif
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

    void simulateWithLoadedUsers(const Vector<UserDevice>& users) {
        IO::printLine("+------------------------------------------+");
        IO::printLine("| Mapping loaded users to frequency        |");
        IO::printLine("| channels...                              |");
        IO::printLine("+------------------------------------------+");
        
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
            int channelIndex = (i / usersPerChannel);
            int effectiveChannel = channelIndex % numChannels;
            
            if (channelIndex >= (numChannels * antennaCount)) {
                dropped++;
                continue;
            }

            if(channels[effectiveChannel].addUser(users[i])) {
                accepted++;
            } else {
                dropped++;
            }
        }
        
        // 3. Print Summary
        IO::print("| Simulation Result: Accepted ");
        IO::printInt(accepted);
        IO::printLine(" users.    |");
        IO::print("| Dropped ");
        IO::printInt(dropped);
        IO::printLine(" users.                         |");
        IO::printLine("+------------------------------------------+");

        // 4. Print Detailed Bandwidth Allocation (users list unchanged)
        IO::printLine("\n==========================================");
        IO::printLine("       BANDWIDTH ALLOCATION REPORT");
        IO::printLine("==========================================");
        
        for(int i=0; i<numChannels; ++i) {
            if (!channels[i].isEmpty()) {
                // Calculate Frequency Band
                float startFreq = i * channelWidthKHz;
                float endFreq = startFreq + channelWidthKHz;
                
                IO::print("Channel ");
                IO::printInt(i + 1);
                IO::print(" (");
                IO::printFloat(startFreq, 1);
                IO::print("-");
                IO::printFloat(endFreq, 1);
                IO::printLine(" kHz):");
                
                // Print users in this band
                channels[i].printUsers();
                IO::printLine("--------------");
            }
        }
        IO::printLine("-----------------------------------");

        // 5. Calculate Core Overhead
        long totalMsgs = (long)accepted * (long)msgPerUser;
        IO::print("Core Overhead Generated: ");
        IO::printFloat(core.calculateOverhead(totalMsgs));
        IO::printLine(" units.");
    }

protected:
    Vector<std::thread*> workerThreads;
    std::mutex channelMutex;

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
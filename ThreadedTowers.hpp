#ifndef THREADEDTOWERS_HPP
#define THREADEDTOWERS_HPP

#include "ThreadedCellTower.hpp"

// --- 2G (GSM) ---
class ThreadedTower2G : public ThreadedCellTower {
public:
    ThreadedTower2G() {
        standardName = "2G (GSM) Threaded";
        totalBandwidthKHz = 1000.0;
        antennaCount = 1;
        usersPerChannel = 16;
        channelWidthKHz = 200.0;
        msgPerUser = 20;
    }

    void simulate() override {
        int numChannels = (int)(totalBandwidthKHz / channelWidthKHz);
        simulateConcurrentUsers(numChannels, usersPerChannel, 1);
    }

    int calculateTotalCapacity() override {
        int numChannels = (int)(totalBandwidthKHz / channelWidthKHz);
        return numChannels * usersPerChannel * antennaCount;
    }

    void printStats() override {
        IO::printLine("--- 2G (GSM) Threaded Statistics ---");
        IO::print("Max Users Supported: ");
        IO::printInt(calculateTotalCapacity());
        IO::printLine("");
        if (!channels.empty()) {
            IO::print("Users in First Channel (200kHz band): ");
            channels[0].printUsers();
        }
        IO::print("Overhead per 100 messages: ");
        IO::printFloat(calculateOverhead());
        IO::printLine("");
    }
};

// --- 3G (UMTS) ---
class ThreadedTower3G : public ThreadedCellTower {
public:
    ThreadedTower3G() {
        standardName = "3G (UMTS) Threaded";
        totalBandwidthKHz = 1000.0;
        antennaCount = 1;
        usersPerChannel = 32;
        channelWidthKHz = 200.0;
        msgPerUser = 10;
    }

    void simulate() override {
        int numChannels = (int)(totalBandwidthKHz / channelWidthKHz);
        simulateConcurrentUsers(numChannels, usersPerChannel, 1000);
    }

    int calculateTotalCapacity() override {
        int numChannels = (int)(totalBandwidthKHz / channelWidthKHz);
        return numChannels * usersPerChannel * antennaCount;
    }

    void printStats() override {
        IO::printLine("--- 3G (UMTS) Threaded Statistics ---");
        IO::print("Max Users Supported: ");
        IO::printInt(calculateTotalCapacity());
        IO::printLine("");
        if (!channels.empty()) {
            IO::print("Users in First Channel: ");
            channels[0].printUsers();
        }
        IO::print("Overhead per 100 messages: ");
        IO::printFloat(calculateOverhead());
        IO::printLine("");
    }
};

// --- 4G (LTE) ---
class ThreadedTower4G : public ThreadedCellTower {
public:
    ThreadedTower4G() {
        standardName = "4G (LTE) Threaded";
        totalBandwidthKHz = 1000.0;
        antennaCount = 4;
        usersPerChannel = 30;
        channelWidthKHz = 10.0;
        msgPerUser = 10;
    }

    void simulate() override {
        int numChannels = (int)(totalBandwidthKHz / channelWidthKHz);
        simulateConcurrentUsers(numChannels, usersPerChannel, 4000);
    }

    int calculateTotalCapacity() override {
        int numChannels = (int)(totalBandwidthKHz / channelWidthKHz);
        return numChannels * usersPerChannel * antennaCount;
    }

    void printStats() override {
        IO::printLine("--- 4G (LTE) Threaded Statistics ---");
        IO::print("Max Users Supported: ");
        IO::printInt(calculateTotalCapacity());
        IO::printLine("");
        if (!channels.empty()) {
            IO::print("Users in First Sub-channel (Antenna 1): ");
            channels[0].printUsers();
        }
        IO::print("Overhead per 100 messages: ");
        IO::printFloat(calculateOverhead());
        IO::printLine("");
    }
};

// --- 5G (NR) ---
class ThreadedTower5G : public ThreadedCellTower {
public:
    ThreadedTower5G() {
        standardName = "5G (NR) Threaded";
        totalBandwidthKHz = 10000.0;
        antennaCount = 16;
        usersPerChannel = 30;
        channelWidthKHz = 1000.0;
        msgPerUser = 10;
    }

    void simulate() override {
        int numChannels = (int)(totalBandwidthKHz / channelWidthKHz);
        simulateConcurrentUsers(numChannels, usersPerChannel, 50000);
    }

    int calculateTotalCapacity() override {
        int numChannels = (int)(totalBandwidthKHz / channelWidthKHz);
        return numChannels * usersPerChannel * antennaCount;
    }

    void printStats() override {
        IO::printLine("--- 5G (NR) Threaded Statistics ---");
        IO::print("Max Users Supported: ");
        IO::printInt(calculateTotalCapacity());
        IO::printLine("");
        if (!channels.empty()) {
            IO::print("Users in First Channel (Antenna 1): ");
            channels[0].printUsers();
        }
        IO::print("Overhead per 100 messages: ");
        IO::printFloat(calculateOverhead());
        IO::printLine("");
    }
};

#endif
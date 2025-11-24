#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "MiniSTL.h"
#include "CellTower.hpp"
#include "Basicio.h"

class Network {
public:
    void addTower(CellTower* tower) {
        towers.push_back(tower);
    }

    void simulateNetwork() {
        for (unsigned long i = 0; i < towers.size(); ++i) {
            towers[i]->simulate();
        }
    }

    void printNetworkStats() {
        for (unsigned long i = 0; i < towers.size(); ++i) {
            towers[i]->printStats();
        }
    }

    void calculateOverhead() {
        for (unsigned long i = 0; i < towers.size(); ++i) {
            IO::print("Overhead per 100 messages for ");
            IO::print(towers[i]->getStandardName());
            IO::print(" is: ");
            IO::printFloat(towers[i]->calculateOverhead());
            IO::printLine(" messages");
        }
    }

private:
    Vector<CellTower*> towers; // Custom Vector
};

#endif
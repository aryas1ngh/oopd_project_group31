#ifndef CELLTOWER_HPP
#define CELLTOWER_HPP

#include "MiniSTL.h"
#include "Basicio.h"
#include "FrequencyChannel.hpp"
#include "UserDevice.hpp"
#include "CellularCore.hpp"

class CellTower {
public:
    virtual void simulate() = 0;
    virtual int calculateTotalCapacity() = 0;
    virtual void printStats() = 0;
    virtual ~CellTower() {}

    const char* getStandardName() const { return standardName.c_str(); }

    float calculateOverhead() const {
        return (float)(msgPerUser * usersPerChannel) / 100.0f;
    }

protected:
    String standardName;
    float totalBandwidthKHz;
    int antennaCount;
    int usersPerChannel;
    float channelWidthKHz;
    int msgPerUser;
    CellularCore core;

    Vector<FrequencyChannel<UserDevice>> channels; // Custom Vector
};

#endif
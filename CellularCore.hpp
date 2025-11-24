#ifndef CELLULARCORE_HPP
#define CELLULARCORE_HPP

#include "Basicio.h"

class CellularCore {
public:
    CellularCore() {}

    // Version 1: Accepts total messages (matches your current ThreadedCellTower call)
    float calculateOverhead(long totalMessages) const {
        if (totalMessages <= 0) return 0.0f;
        // Project Logic: Overhead per 100 messages
        return (float)totalMessages / 100.0f;
    }

    // Version 2: Accepts users + msgs/user (Overload for backward compatibility)
    float calculateOverhead(int numUsers, int msgsPerUser) const {
        long totalMessages = (long)numUsers * (long)msgsPerUser;
        return calculateOverhead(totalMessages);
    }

    // Returns required cores based on total capacity needs
    int calculateRequiredCores(int totalMessages, int capacityPerCore) {
        if (capacityPerCore <= 0) return 1;
        int cores = totalMessages / capacityPerCore;
        if (totalMessages % capacityPerCore != 0) cores++;
        return cores;
    }
};

#endif
#ifndef FREQUENCYCHANNEL_HPP
#define FREQUENCYCHANNEL_HPP

#include "MiniSTL.h"
#include "Basicio.h"
#include "UserDevice.hpp"

template <typename T>
class FrequencyChannel {
public:
    FrequencyChannel(int maxUsers) : maxUsers(maxUsers) {}
    FrequencyChannel() : maxUsers(0) {} // Default constructor

    bool addUser(const T& user) {
        if ((int)connectedUsers.size() < maxUsers) {
            connectedUsers.push_back(user);
            return true;
        }
        return false;
    }

    // New helper to avoid printing empty channels
    bool isEmpty() const {
        return connectedUsers.empty();
    }

    void printUsers() const {
        // Only print the loop content (header is handled by caller for better formatting)
        for (unsigned long i = 0; i < connectedUsers.size(); ++i) {
            IO::print("    [User ID: ");
            IO::printInt(connectedUsers[i].getID());
            IO::printLine("]");
        }
    }

private:
    int maxUsers;
    Vector<T> connectedUsers;  // Custom Vector
};

#endif
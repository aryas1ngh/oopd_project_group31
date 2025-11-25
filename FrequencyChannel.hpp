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

    bool isEmpty() const {
        return connectedUsers.empty();
    }

    void printUsers() const {
        IO::print("    Users: ");
        for (unsigned long i = 0; i < connectedUsers.size(); ++i) {
            IO::print("[");
            IO::printInt(connectedUsers[i].getID());
            IO::print("] ");
        }
        IO::printLine(""); // One newline at the very end
    }

private:
    int maxUsers;
    Vector<T> connectedUsers;  // Custom Vector
};

#endif
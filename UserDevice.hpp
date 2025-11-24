#ifndef USERDEVICE_HPP
#define USERDEVICE_HPP

#include "Basicio.h"

class UserDevice {
public:
    UserDevice(int id) : id(id) {}
    UserDevice() : id(0) {} // Default needed for Vector

    int getID() const { return id; }
    void setID(int newID) { id = newID; }

private:
    int id; 
};

#endif
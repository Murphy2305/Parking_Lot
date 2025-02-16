#pragma once
#include <bits/stdc++.h>
#include "./IVehicle.h"
using namespace std;

class IParkingFloor
{
public:
    virtual pair<bool, vector<int>> findAvailableSpots(int spotsNeeded) = 0;
    virtual bool parkVehicle(const vector<int> &spotNumbers, shared_ptr<IVehicle> vehicle) = 0;
    virtual bool removeVehicle(const string &licensePlate) = 0;
    virtual int getAvailableSpots() = 0;
    virtual vector<int> getVehicleLocation(const string &licensePlate) = 0;
};

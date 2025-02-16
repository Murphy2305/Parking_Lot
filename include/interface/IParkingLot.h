#pragma once
#include <bits/stdc++.h>
using namespace std;

class IParkingLot
{
public:
    virtual bool parkVehicle(const string &licensePlate, const string &vehicleType) = 0;
    virtual bool removeVehicle(const string &licensePlate) = 0;
    virtual pair<int, vector<int>> getVehicleLocation(const string &licensePlate) = 0;
    virtual bool isFull() = 0;
    virtual vector<int> getAvailableSpotsPerFloor() = 0;
};
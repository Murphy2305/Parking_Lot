#pragma once
#include <bits/stdc++.h>
using namespace std;

class IVehicle
{
public:
    virtual int getRequiredSpot() = 0;
    virtual string getVehicleType() = 0;
    virtual string getLicensePlate() = 0;
};
#pragma once
#include <bits/stdc++.h>
#include "../../include/interface/IVehicle.h"
using namespace std;

class Truck : public IVehicle
{
private:
    string licensePlate;

public:
    Truck(const string &plate)
    {
        licensePlate = plate;
    }

    int getRequiredSpot() override
    {
        return 2;
    }
    string getVehicleType() override
    {
        return "Truck";
    }
    string getLicensePlate() override
    {
        return licensePlate;
    }
};
#pragma once
#include <bits/stdc++.h>
#include "../../include/interface/IVehicle.h"
using namespace std;

class Bike : public IVehicle
{
private:
    string licensePlate;

public:
    Bike(const string &plate)
    {
        licensePlate = plate;
    }

    int getRequiredSpot() override
    {
        return 1;
    }
    string getVehicleType() override
    {
        return "Bike";
    }
    string getLicensePlate() override
    {
        return licensePlate;
    }
};
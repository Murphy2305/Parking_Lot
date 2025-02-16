#pragma once
#include <bits/stdc++.h>
#include "../../include/interface/IVehicle.h"
using namespace std;

class Car : public IVehicle
{
private:
    string licensePlate;

public:
    Car(const string &plate)
    {
        licensePlate = plate;
    }

    int getRequiredSpot() override
    {
        return 1;
    }
    string getVehicleType() override
    {
        return "Car";
    }
    string getLicensePlate() override
    {
        return licensePlate;
    }
};
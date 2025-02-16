#pragma once
#include <bits/stdc++.h>
#include "../../include/interface/IVehicleFactory.h"
#include "../../include/interface/IVehicle.h"
#include "../vehicles/Bike.h"
#include "../vehicles/Car.h"
#include "../vehicles/Truck.h"

using namespace std;

class VehicleFactory : public IVehicleFactory
{
public:
    shared_ptr<IVehicle> createVehicle(const string &type, const string &licensePlate) override
    {
        if (type == "Bike")
            return make_shared<Bike>(licensePlate);
        if (type == "Car")
            return make_shared<Car>(licensePlate);
        if (type == "Truck")
            return make_shared<Truck>(licensePlate);
        throw invalid_argument("Invalid vehicle type");
    }
};

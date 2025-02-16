#pragma once
#include <bits/stdc++.h>
#include "./IVehicle.h"
using namespace std;

class IVehicleFactory
{

public:
    virtual shared_ptr<IVehicle> createVehicle(const string &type, const string &licensePlate) = 0;
};
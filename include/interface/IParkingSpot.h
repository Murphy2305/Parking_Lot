#include "./IVehicle.h"
#include <bits/stdc++.h>

using namespace std;

class IParkingSpot
{
public:
    virtual bool occupy(shared_ptr<IVehicle> vehicle) = 0;
    virtual bool vacate() = 0;
    virtual bool isAvailable() = 0;
    virtual int getSpotNumber() = 0;
    virtual IVehicle *getParkedVehicle() = 0;
};

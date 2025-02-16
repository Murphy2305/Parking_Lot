#include "../../../include/interface/IParkingSpot.h"
#include <bits/stdc++.h>
using namespace std;

class ParkingSpot
{
private:
    int spotNumber;
    bool isOccupied;
    shared_ptr<IVehicle> parkedVehicle;

public:
    ParkingSpot(int number)
    {
        spotNumber = number;
        isOccupied = false;
    }

    bool occupy(shared_ptr<IVehicle> vehicle)
    {
        if (!isOccupied && vehicle)
        {
            parkedVehicle = vehicle; // shared_ptr can be copied
            isOccupied = true;
            return true;
        }
        return false;
    }

    bool vacate()
    {
        if (isOccupied)
        {
            parkedVehicle.reset();
            isOccupied = false;
            return true;
        }
        return false;
    }

    bool isAvailable()
    {
        return !isOccupied;
    }

    int getSpotNumber()
    {
        return spotNumber;
    }

    IVehicle *getParkedVehicle()
    {
        return parkedVehicle.get();
    }
};

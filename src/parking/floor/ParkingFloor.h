#include "../../../include/interface/IParkingFloor.h"
#include "../../../include/interface/IVehicle.h"
#include "../spot/ParkingSpot.h"
#include <bits/stdc++.h>
#include "../../../utils/SpinLock.h"
using namespace std;

class ParkingFloor : public IParkingFloor
{
private:
    int floorNumber;
    vector<unique_ptr<ParkingSpot>> spots;
    SpinLock floorLock;

public:
    ParkingFloor(int number, int totalSpots)
    {
        floorNumber = number;
        for (int i = 0; i < totalSpots; ++i)
        {
            spots.push_back(make_unique<ParkingSpot>(i));
        }
    }

    pair<bool, vector<int>> findAvailableSpots(int spotsNeeded) override
    {
        floorLock.lock();

        vector<int> availableSpots;

        for (size_t i = 0; i < spots.size(); ++i)
        {
            if (spots[i]->isAvailable())
            {
                availableSpots.clear();
                bool consecutive = true;

                for (size_t j = 0; j < spotsNeeded && (i + j) < spots.size(); ++j)
                {
                    if (!spots[i + j]->isAvailable())
                    {
                        consecutive = false;
                        break;
                    }
                    availableSpots.push_back(i + j);
                }

                if (consecutive && availableSpots.size() == spotsNeeded)
                {
                    auto result = make_pair(true, availableSpots);
                    floorLock.unlock();
                    return result;
                }
            }
        }

        floorLock.unlock();
        return {false, {}};
    }

    bool parkVehicle(const vector<int> &spotNumbers, shared_ptr<IVehicle> vehicle) override
    {
        floorLock.lock();

        for (int spotNum : spotNumbers)
        {
            if (spotNum >= spots.size() || !spots[spotNum]->isAvailable())
            {
                floorLock.unlock();
                return false;
            }
        }

        for (int spotNum : spotNumbers)
        {
            if (!spots[spotNum]->occupy(vehicle))
            {
                for (int i : spotNumbers)
                {
                    spots[i]->vacate();
                }
                floorLock.unlock();
                return false;
            }
        }

        floorLock.unlock();
        return true;
    }

    bool removeVehicle(const string &licensePlate) override
    {
        floorLock.lock();

        bool removed = false;

        for (auto &spot : spots)
        {
            auto vehicle = spot->getParkedVehicle();
            if (vehicle && vehicle->getLicensePlate() == licensePlate)
            {
                spot->vacate();
                removed = true;
            }
        }

        floorLock.unlock();
        return removed;
    }

    int getAvailableSpots() override
    {
        floorLock.lock();

        int count = 0;
        for (const auto &spot : spots)
        {
            if (spot->isAvailable())
            {
                count++;
            }
        }

        floorLock.unlock();
        return count;
    }

    vector<int> getVehicleLocation(const string &licensePlate) override
    {
        floorLock.lock();

        vector<int> location;
        for (const auto &spot : spots)
        {
            auto vehicle = spot->getParkedVehicle();
            if (vehicle && vehicle->getLicensePlate() == licensePlate)
            {
                location.push_back(spot->getSpotNumber());
            }
        }

        floorLock.unlock();
        return location;
    }
};
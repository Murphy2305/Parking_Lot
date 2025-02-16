// File: ParkingLot.h
#pragma once
#include <bits/stdc++.h>
#include <atomic>
#include "../../../include/interface/IParkingFloor.h"
#include "../../../include/interface/IParkingLot.h"
#include "../../../include/interface/IVehicleFactory.h"
#include "../floor/ParkingFloor.h"
#include "../../factories/VehicleFactory.h"

using namespace std;

class SpinLock
{
private:
    atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void lock()
    {
        while (flag.test_and_set(memory_order_acquire))
            ;
    }

    void unlock()
    {
        flag.clear(memory_order_release);
    }
};

class ParkingLot : public IParkingLot
{
private:
    vector<unique_ptr<IParkingFloor>> floors;
    unordered_map<string, pair<int, vector<int>>> vehicleLocations;
    unique_ptr<IVehicleFactory> vehicleFactory;
    SpinLock parkingLock;

public:
    ParkingLot(int numFloors, int spotsPerFloor)
    {
        vehicleFactory = make_unique<VehicleFactory>();
        for (int i = 0; i < numFloors; ++i)
        {
            floors.push_back(make_unique<ParkingFloor>(i, spotsPerFloor));
        }
    }

    bool parkVehicle(const string &licensePlate, const string &vehicleType) override
    {
        parkingLock.lock();

        if (vehicleLocations.find(licensePlate) != vehicleLocations.end())
        {
            parkingLock.unlock();
            return false;
        }

        try
        {
            shared_ptr<IVehicle> vehicle = vehicleFactory->createVehicle(vehicleType, licensePlate);
            int spotsNeeded = vehicle->getRequiredSpot();

            for (size_t i = 0; i < floors.size(); ++i)
            {
                auto floorTest = floors[i]->findAvailableSpots(spotsNeeded);
                bool found = floorTest.first;
                vector<int> spots = floorTest.second;
                if (found && floors[i]->parkVehicle(spots, vehicle))
                {
                    vehicleLocations[licensePlate] = {i, spots};
                    parkingLock.unlock();
                    return true;
                }
            }
        }
        catch (const invalid_argument &e)
        {
            parkingLock.unlock();
            return false;
        }

        parkingLock.unlock();
        return false;
    }

    bool removeVehicle(const string &licensePlate) override
    {
        parkingLock.lock();

        auto it = vehicleLocations.find(licensePlate);
        if (it != vehicleLocations.end())
        {
            int floorNumber = it->second.first;
            bool removed = floors[floorNumber]->removeVehicle(licensePlate);
            if (removed)
            {
                vehicleLocations.erase(it);
                parkingLock.unlock();
                return true;
            }
        }

        parkingLock.unlock();
        return false;
    }

    pair<int, vector<int>> getVehicleLocation(const string &licensePlate) override
    {
        parkingLock.lock();

        auto it = vehicleLocations.find(licensePlate);
        if (it != vehicleLocations.end())
        {
            auto result = it->second;
            parkingLock.unlock();
            return result;
        }

        parkingLock.unlock();
        return {-1, vector<int>()};
    }

    bool isFull() override
    {
        parkingLock.lock();

        for (const auto &floor : floors)
        {
            if (floor->getAvailableSpots() > 0)
            {
                parkingLock.unlock();
                return false;
            }
        }

        parkingLock.unlock();
        return true;
    }

    vector<int> getAvailableSpotsPerFloor() override
    {
        parkingLock.lock();

        vector<int> availableSpots;
        for (const auto &floor : floors)
        {
            availableSpots.push_back(floor->getAvailableSpots());
        }

        parkingLock.unlock();
        return availableSpots;
    }
};
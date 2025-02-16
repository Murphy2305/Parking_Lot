#include "./src/parking/lot/ParkingLot.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int numFloors, spotsPerFloor;

    while (true)
    {
        cout << "Enter number of floors: ";
        if (!(cin >> numFloors) || numFloors <= 0)
        {
            cout << "Invalid input. Please enter a positive integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        cout << "Enter number of spots per floor: ";
        if (!(cin >> spotsPerFloor) || spotsPerFloor <= 0)
        {
            cout << "Invalid input. Please enter a positive integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }

    ParkingLot parkingLot(numFloors, spotsPerFloor);

    int choice;
    string licensePlate, vehicleType;
    bool running = true;

    while (running)
    {
        cout << "\n========== PARKING LOT SYSTEM ==========\n";
        cout << "1. Park a vehicle" << endl;
        cout << "2. Remove a vehicle" << endl;
        cout << "3. Get vehicle location" << endl;
        cout << "4. Show available spots per floor" << endl;
        cout << "5. Check if parking lot is full" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            cin >> ws;
            getline(cin, licensePlate);
            getline(cin, vehicleType);
            cout << "Parking " << vehicleType << " " << licensePlate << ": "
                 << (parkingLot.parkVehicle(licensePlate, vehicleType) ? "Success" : "Failed") << endl;
            break;

        case 2:
            cin >> ws;
            getline(cin, licensePlate);
            cout << "Removing vehicle " << licensePlate << ": "
                 << (parkingLot.removeVehicle(licensePlate) ? "Success" : "Failed") << endl;
            break;

        case 3:
        {
            cin >> ws;
            getline(cin, licensePlate);
            pair<int, vector<int>> location = parkingLot.getVehicleLocation(licensePlate);
            int floor = location.first;
            vector<int> spots = location.second;

            if (floor != -1)
            {
                cout << "Vehicle " << licensePlate << " is parked on floor " << floor << " at spots: ";
                for (int spot : spots)
                    cout << spot << " ";
                cout << endl;
            }
            else
            {
                cout << "Vehicle " << licensePlate << " not found in the parking lot." << endl;
            }
            break;
        }

        case 4:
        {
            vector<int> availableSpots = parkingLot.getAvailableSpotsPerFloor();
            for (size_t i = 0; i < availableSpots.size(); ++i)
                cout << "Floor " << i << ": " << availableSpots[i] << " spots" << endl;
            break;
        }

        case 5:
            cout << "Is parking lot full? " << (parkingLot.isFull() ? "Yes" : "No") << endl;
            break;

        case 6:
            cout << "Exiting program. Goodbye!" << endl;
            running = false;
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            break;
        }
    }
    return 0;
}

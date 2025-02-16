#include "./src/parking/lot/ParkingLot.h"
#include <iostream>
#include <string>
#include <limits>

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    int numFloors, spotsPerFloor;

    cout << "Enter number of floors: ";
    cin >> numFloors;

    cout << "Enter number of spots per floor: ";
    cin >> spotsPerFloor;

    ParkingLot parkingLot(numFloors, spotsPerFloor);

    int choice;
    string licensePlate, vehicleType;
    bool running = true;

    while (running)
    {
        cout << "\n========== PARKING LOT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Park a vehicle\n";
        cout << "2. Remove a vehicle\n";
        cout << "3. Get vehicle location\n";
        cout << "4. Show available spots per floor\n";
        cout << "5. Check if parking lot is full\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            clearInputBuffer();
            cout << "Enter license plate: ";
            getline(cin, licensePlate);

            cout << "Enter vehicle type (Car/Truck/Bike): ";
            getline(cin, vehicleType);

            bool success = parkingLot.parkVehicle(licensePlate, vehicleType);
            cout << "Parking " << vehicleType << " " << licensePlate << ": "
                 << (success ? "Success" : "Failed") << endl;
            break;
        }

        case 2:
        {
            clearInputBuffer();
            cout << "Enter license plate of vehicle to remove: ";
            getline(cin, licensePlate);

            bool success = parkingLot.removeVehicle(licensePlate);
            cout << "Removing vehicle " << licensePlate << ": "
                 << (success ? "Success" : "Failed") << endl;
            break;
        }

        case 3:
        {
            clearInputBuffer();
            cout << "Enter license plate to locate: ";
            getline(cin, licensePlate);

            int floor = parkingLot.getVehicleLocation(licensePlate).first;
            vector<int> spots = parkingLot.getVehicleLocation(licensePlate).second;

            if (floor != -1)
            {
                cout << "Vehicle " << licensePlate << " is parked on floor " << floor << " at spots: ";
                for (int spot : spots)
                {
                    cout << spot << " ";
                }
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
            auto availableSpots = parkingLot.getAvailableSpotsPerFloor();
            cout << "Available spots per floor:" << endl;
            for (size_t i = 0; i < availableSpots.size(); ++i)
            {
                cout << "Floor " << i << ": " << availableSpots[i] << " spots" << endl;
            }
            break;
        }

        case 5:
        {
            cout << "Is parking lot full? "
                 << (parkingLot.isFull() ? "Yes" : "No") << endl;
            break;
        }

        case 6:
        {
            cout << "Exiting program. Goodbye!" << endl;
            running = false;
            break;
        }

        default:
        {
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            break;
        }
        }
    }

    return 0;
}
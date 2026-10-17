
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
using namespace std;

struct Vehicle {
    string ownerName;
    string vehicleNumber;
    int slotNumber;
    int hours;
};

int main() {
    map<string, Vehicle> parkedVehicles;
    set<int> availableSlots;
    vector<Vehicle> parkingHistory;

    const int TOTAL_SLOTS = 10;
    const double RATE_PER_HOUR = 20.0;
    int choice;

    for (int i = 1; i <= TOTAL_SLOTS; i++) {
        availableSlots.insert(i);
    }

    do {
        cout << "\n===== SMART PARKING SYSTEM =====\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Display Parked Vehicles\n";
        cout << "4. Search Vehicle\n";
        cout << "5. Display Available Slots\n";
        cout << "6. Display Parking Revenue\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (availableSlots.empty()) {
                cout << "Parking is full!\n";
                continue;
            }

            Vehicle v;

            cout << "Enter Vehicle Number: ";
            cin >> v.vehicleNumber;

            if (parkedVehicles.count(v.vehicleNumber)) {
                cout << "Vehicle is already parked!\n";
                continue;
            }

            cin.ignore();
            cout << "Enter Owner Name: ";
            getline(cin, v.ownerName);

            cout << "\nAvailable Slots: ";
            for (int slot : availableSlots) {
                cout << slot << " ";
            }

            cout << "\nChoose Slot Number: ";
            cin >> v.slotNumber;

            auto it = availableSlots.find(v.slotNumber);

            if (it == availableSlots.end()) {
                cout << "Invalid or occupied slot!\n";
                continue;
            }

            v.hours = 0;

            parkedVehicles[v.vehicleNumber] = v;
            availableSlots.erase(it);

            cout << "Vehicle parked successfully!\n";
            cout << "Vehicle Number: " << v.vehicleNumber << "\n";
            cout << "Slot Number: " << v.slotNumber << "\n";
        }
        else if (choice == 2) {
            string number;
            int hours;

            cout << "Enter Vehicle Number: ";
            cin >> number;

            auto it = parkedVehicles.find(number);

            if (it == parkedVehicles.end()) {
                cout << "Vehicle not found!\n";
                continue;
            }

            cout << "Enter parking duration in hours: ";
            cin >> hours;

            if (hours <= 0) {
                cout << "Duration must be positive!\n";
                continue;
            }

            Vehicle v = it->second;
            v.hours = hours;

            double fee = hours * RATE_PER_HOUR;

            parkingHistory.push_back(v);
            availableSlots.insert(v.slotNumber);
            parkedVehicles.erase(it);

            cout << fixed << setprecision(2);
            cout << "\nVehicle removed successfully!\n";
            cout << "Owner: " << v.ownerName << "\n";
            cout << "Parking Duration: " << hours << " hours\n";
            cout << "Parking Fee: Rs. " << fee << "\n";
        }
        else if (choice == 3) {
            if (parkedVehicles.empty()) {
                cout << "No vehicles currently parked.\n";
            }

            for (const auto &item : parkedVehicles) {
                const Vehicle &v = item.second;

                cout << "\nVehicle Number: " << v.vehicleNumber
                     << "\nOwner: " << v.ownerName
                     << "\nSlot: " << v.slotNumber << "\n";
            }
        }
        else if (choice == 4) {
            string number;

            cout << "Enter Vehicle Number to search: ";
            cin >> number;

            auto it = parkedVehicles.find(number);

            if (it != parkedVehicles.end()) {
                cout << "Vehicle Found!\n";
                cout << "Owner: " << it->second.ownerName << "\n";
                cout << "Slot: " << it->second.slotNumber << "\n";
            } else {
                cout << "Vehicle is not currently parked.\n";
            }
        }
        else if (choice == 5) {
            cout << "\nAvailable Parking Slots: ";

            if (availableSlots.empty()) {
                cout << "None";
            } else {
                for (int slot : availableSlots) {
                    cout << slot << " ";
                }
            }

            cout << "\nAvailable Slot Count: "
                 << availableSlots.size() << "\n";
        }
        else if (choice == 6) {
            double revenue = 0;

            for (const Vehicle &v : parkingHistory) {
                revenue += v.hours * RATE_PER_HOUR;
            }

            cout << fixed << setprecision(2);
            cout << "Total Collected Parking Fees: Rs. "
                 << revenue << "\n";
        }
        else if (choice == 7) {
            cout << "Exiting Smart Parking System...\n";
        }
        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}

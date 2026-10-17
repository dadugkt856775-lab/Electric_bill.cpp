
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Customer {
    int id;
    string name;
    int units;
    double bill;

    Customer(int i, string n, int u)
        : id(i), name(n), units(u), bill(0) {}
};

double calculateBill(int units) {
    double amount = 0;

    // Example tariff slabs
    if (units <= 100) {
        amount = units * 3.0;
    }
    else if (units <= 200) {
        amount = 100 * 3.0 + (units - 100) * 5.0;
    }
    else if (units <= 300) {
        amount = 100 * 3.0 + 100 * 5.0
                 + (units - 200) * 7.0;
    }
    else {
        amount = 100 * 3.0 + 100 * 5.0
                 + 100 * 7.0 + (units - 300) * 8.0;
    }

    return amount;
}

int main() {
    map<int, Customer> customers;
    int choice;

    do {
        cout << "\n===== ELECTRICITY BILL MANAGEMENT =====\n";
        cout << "1. Add Customer\n";
        cout << "2. Display All Bills\n";
        cout << "3. Search Customer\n";
        cout << "4. Update Units Consumed\n";
        cout << "5. Sort Customers by Bill\n";
        cout << "6. Calculate Total Revenue\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, units;
            string name;

            cout << "Enter Customer ID: ";
            cin >> id;

            if (customers.count(id)) {
                cout << "Customer ID already exists!\n";
                continue;
            }

            cin.ignore();
            cout << "Enter Customer Name: ";
            getline(cin, name);

            cout << "Enter Units Consumed: ";
            cin >> units;

            if (units < 0) {
                cout << "Units cannot be negative!\n";
                continue;
            }

            Customer c(id, name, units);
            c.bill = calculateBill(units);

            customers.emplace(id, c);
            cout << "Customer added successfully!\n";
        }
        else if (choice == 2) {
            if (customers.empty()) {
                cout << "No customer records available.\n";
            }

            cout << fixed << setprecision(2);

            for (const auto &item : customers) {
                const Customer &c = item.second;

                cout << "\nCustomer ID: " << c.id
                     << "\nName: " << c.name
                     << "\nUnits: " << c.units
                     << "\nBill: Rs. " << c.bill << "\n";
            }
        }
        else if (choice == 3) {
            int id;

            cout << "Enter Customer ID: ";
            cin >> id;

            auto it = customers.find(id);

            if (it != customers.end()) {
                const Customer &c = it->second;

                cout << fixed << setprecision(2);
                cout << "\nCustomer Found!\n";
                cout << "Name: " << c.name << "\n";
                cout << "Units: " << c.units << "\n";
                cout << "Electricity Bill: Rs. "
                     << c.bill << "\n";
            } else {
                cout << "Customer not found!\n";
            }
        }
        else if (choice == 4) {
            int id, units;

            cout << "Enter Customer ID: ";
            cin >> id;

            auto it = customers.find(id);

            if (it == customers.end()) {
                cout << "Customer not found!\n";
                continue;
            }

            cout << "Enter New Units Consumed: ";
            cin >> units;

            if (units < 0) {
                cout << "Units cannot be negative!\n";
                continue;
            }

            it->second.units = units;
            it->second.bill = calculateBill(units);

            cout << "Bill updated successfully!\n";
        }
        else if (choice == 5) {
            vector<Customer> sortedCustomers;

            for (const auto &item : customers) {
                sortedCustomers.push_back(item.second);
            }

            sort(sortedCustomers.begin(), sortedCustomers.end(),
                [](const Customer &a, const Customer &b) {
                    return a.bill > b.bill;
                });

            cout << fixed << setprecision(2);
            cout << "\n===== CUSTOMERS SORTED BY BILL =====\n";

            for (const Customer &c : sortedCustomers) {
                cout << c.name << " - Rs. "
                     << c.bill << "\n";
            }
        }
        else if (choice == 6) {
            double total = 0;

            for (const auto &item : customers) {
                total += item.second.bill;
            }

            cout << fixed << setprecision(2);
            cout << "Total Revenue: Rs. "
                 << total << "\n";
        }
        else if (choice == 7) {
            cout << "Exiting Electricity Bill System...\n";
        }
        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}

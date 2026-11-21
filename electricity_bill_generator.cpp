#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class ElectricityBill {
private:
    string consumerId;
    string customerName;
    string address;
    string meterNumber;
    double unitsConsumed;
    double fixedCharge;
    double energyCharge;
    double taxAmount;
    double totalBill;

public:
    // Default constructor
    ElectricityBill()
        : consumerId(""), customerName(""), address(""), meterNumber(""),
          unitsConsumed(0.0), fixedCharge(50.0), energyCharge(0.0),
          taxAmount(0.0), totalBill(0.0) {}

    // Parameterized constructor
    ElectricityBill(string id, string name, string addr, string meterNo, double units, double fixed = 50.0)
        : consumerId(id), customerName(name), address(addr), meterNumber(meterNo),
          unitsConsumed(units), fixedCharge(fixed), energyCharge(0.0),
          taxAmount(0.0), totalBill(0.0) {
        calculateBill();
    }

    // Input consumer details and units
    void inputDetails() {
        cout << "=== Enter Consumer Details ===" << endl;
        cout << "Consumer ID     : ";
        getline(cin >> ws, consumerId);

        cout << "Customer Name   : ";
        getline(cin, customerName);

        cout << "Address         : ";
        getline(cin, address);

        cout << "Meter Number    : ";
        getline(cin, meterNumber);

        do {
            cout << "Units Consumed  : ";
            cin >> unitsConsumed;
            if (unitsConsumed < 0) {
                cout << "Units cannot be negative. Please enter a valid value.\n";
            }
        } while (unitsConsumed < 0);

        calculateBill();
    }

    // Calculate bill using predefined tariff slabs
    // Slab 1: First 100 units @ Rs. 3.50 / unit
    // Slab 2: Next 100 units (101 - 200) @ Rs. 5.00 / unit
    // Slab 3: Next 200 units (201 - 400) @ Rs. 6.75 / unit
    // Slab 4: Above 400 units @ Rs. 8.50 / unit
    void calculateBill() {
        energyCharge = 0.0;
        double remainingUnits = unitsConsumed;

        if (remainingUnits > 0) {
            double slab1Units = (remainingUnits > 100.0) ? 100.0 : remainingUnits;
            energyCharge += slab1Units * 3.50;
            remainingUnits -= slab1Units;
        }

        if (remainingUnits > 0) {
            double slab2Units = (remainingUnits > 100.0) ? 100.0 : remainingUnits;
            energyCharge += slab2Units * 5.00;
            remainingUnits -= slab2Units;
        }

        if (remainingUnits > 0) {
            double slab3Units = (remainingUnits > 200.0) ? 200.0 : remainingUnits;
            energyCharge += slab3Units * 6.75;
            remainingUnits -= slab3Units;
        }

        if (remainingUnits > 0) {
            energyCharge += remainingUnits * 8.50;
        }

        double subtotal = fixedCharge + energyCharge;
        taxAmount = subtotal * 0.05; // 5% electricity duty / tax
        totalBill = subtotal + taxAmount;
    }

    // Display the formatted final bill
    void displayBill() const {
        cout << "\n========================================================" << endl;
        cout << "               ELECTRICITY BILL RECEIPT               " << endl;
        cout << "========================================================" << endl;
        cout << left << setw(20) << "Consumer ID"    << ": " << consumerId << endl;
        cout << left << setw(20) << "Customer Name"  << ": " << customerName << endl;
        cout << left << setw(20) << "Address"        << ": " << address << endl;
        cout << left << setw(20) << "Meter Number"   << ": " << meterNumber << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << fixed << setprecision(2);
        cout << left << setw(20) << "Units Consumed" << ": " << unitsConsumed << " kWh" << endl;
        cout << left << setw(20) << "Fixed Charge"   << ": Rs. " << fixedCharge << endl;
        cout << left << setw(20) << "Energy Charge"  << ": Rs. " << energyCharge << endl;
        cout << left << setw(20) << "Electricity Tax (5%)" << ": Rs. " << taxAmount << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << left << setw(20) << "Total Payable"  << ": Rs. " << totalBill << endl;
        cout << "========================================================" << endl;
    }
};

int main() {
    cout << "Welcome to the Electricity Bill Generator System\n" << endl;

    // Example using parameterized constructor
    ElectricityBill sampleCustomer(
        "CID1001",
        "Aarav Sharma",
        "42 MG Road, Bengaluru",
        "MTR-88921",
        265.0
    );
    cout << "[Sample Bill Generated via Parameterized Constructor]";
    sampleCustomer.displayBill();

    // Interactive customer bill generation using default constructor & input method
    char choice;
    cout << "\nDo you want to generate a bill for a new consumer? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        ElectricityBill newCustomer;
        newCustomer.inputDetails();
        newCustomer.displayBill();
    }

    cout << "\nThank you for using the Electricity Bill Generator!" << endl;
    return 0;
}

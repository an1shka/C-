#include <iostream>
using namespace std;

int main() {
    long long balance = 1000;
    int choice;
    do {
        cout << "===== WALLET =====\n1. Check balance\n2. Deposit money\n"
                "3. Spend money\n0. Exit\nChoose: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Balance: " << balance << '\n';
        } else if (choice == 2) {
            long long amount;
            cout << "Amount: ";
            cin >> amount;
            if (amount > 0) {
                balance += amount;
                cout << "Deposit successful!\n";
            } else cout << "Invalid amount!\n";
        } else if (choice == 3) {
            long long amount;
            cout << "Amount: ";
            cin >> amount;
            if (amount <= 0) cout << "Invalid amount!\n";
            else if (amount > balance) cout << "Not enough money!\n";
            else {
                balance -= amount;
                cout << "Payment successful!\n";
            }
        } else if (choice != 0) cout << "Unknown command!\n";
    } while (choice != 0);
    cout << "Goodbye!\n";
}

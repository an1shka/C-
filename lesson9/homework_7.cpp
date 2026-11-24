#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;
int main() {
    double balance = 150000, dailyLimit = 100000;
    const int correctPin = 4321;
    int pin, vip, operation;
    cin >> pin >> vip;
    if (pin != correctPin) { cout << "ACCESS DENIED\nReason: Incorrect PIN\n"; return 0; }
    if (vip != 0 && vip != 1) { cout << "Invalid input\n"; return 0; }
    cin >> operation;
    cout << fixed << setprecision(2);
    if (operation == 1) cout << "Balance: " << balance << " KZT\n";
    else if (operation == 2) {
        double amount; cin >> amount;
        if (amount <= 0) cout << "Operation denied: invalid amount\n";
        else { balance += amount; cout << "New balance: " << balance << " KZT\n"; }
    } else if (operation == 3) {
        double amount; cin >> amount;
        double commission = vip == 1 || amount <= 50000 ? 0 : amount * 0.02;
        if (amount <= 0) cout << "Operation denied: invalid amount\n";
        else if (amount > dailyLimit) cout << "Operation denied: daily limit exceeded\n";
        else if (amount + commission > balance) cout << "Operation denied: insufficient funds\n";
        else {
            balance -= amount + commission; dailyLimit -= amount;
            cout << "Withdrawal: " << amount << " KZT\nCommission: " << commission
                 << " KZT\nNew balance: " << balance << " KZT\nRemaining daily limit: " << dailyLimit << " KZT\n";
        }
    } else if (operation == 4) {
        double amount; cin >> amount;
        double commission = vip == 1 ? 0 : max(amount * 0.01, 200.0);
        if (amount <= 0) cout << "Operation denied: invalid amount\n";
        else if (amount + commission > balance) cout << "Operation denied: insufficient funds\n";
        else {
            balance -= amount + commission;
            cout << "Transfer: " << amount << " KZT\nCommission: " << commission
                 << " KZT\nNew balance: " << balance << " KZT\n";
        }
    } else cout << "Invalid operation\n";
}

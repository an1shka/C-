#include <iostream>
using namespace std;

void deposit(int& balance, int amount) {
    if (amount > 0) balance += amount;
}
bool withdraw(int& balance, int amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    return true;
}

int main() {
    int balance = 50000;
    cout << "Initial balance: " << balance << '\n';
    deposit(balance, 20000);
    cout << "Deposit: 20000\nBalance: " << balance << '\n';
    cout << "Withdraw: 30000\n";
    if (!withdraw(balance, 30000)) cout << "Not enough money!\n";
    cout << "Balance: " << balance << "\nWithdraw: 50000\n";
    if (!withdraw(balance, 50000)) cout << "Not enough money!\n";
    cout << "Balance: " << balance << '\n';
}

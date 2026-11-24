#include <iostream>
#include <memory>
#include <string>
using namespace std;

struct BankAccount {
    string owner;
    int balance;
};

void deposit(BankAccount* account, int amount) {
    if (account != nullptr && amount > 0) account->balance += amount;
}

void withdraw(BankAccount* account, int amount) {
    if (account == nullptr || amount <= 0) return;
    cout << "Withdraw: " << amount << '\n';
    if (amount > account->balance) cout << "Not enough money!\n";
    else account->balance -= amount;
}

int main() {
    auto account = make_unique<BankAccount>(BankAccount{"Ali", 10000});
    cout << "Owner: " << account->owner << "\nInitial balance: " << account->balance << '\n';
    deposit(account.get(), 5000);
    cout << "Deposit: 5000\nBalance: " << account->balance << '\n';
    withdraw(account.get(), 3000);
    cout << "Balance: " << account->balance << '\n';
    withdraw(account.get(), 20000);
    cout << "Final balance: " << account->balance << '\n';
}

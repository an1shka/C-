#include <iostream>
#include <string>
using namespace std;

struct BankAccount { string owner; int balance; };
void deposit(BankAccount* account, int amount) {
    if (account != nullptr && amount > 0) account->balance += amount;
}
bool withdraw(BankAccount* account, int amount) {
    if (account == nullptr || amount <= 0 || amount > account->balance) return false;
    account->balance -= amount;
    return true;
}
bool transfer(BankAccount* from, BankAccount* to, int amount) {
    if (from == nullptr || to == nullptr || amount <= 0 || amount > from->balance) return false;
    from->balance -= amount;
    to->balance += amount;
    return true;
}
void printAccount(BankAccount account) {
    cout << account.owner << " balance: " << account.balance << '\n';
}

int main() {
    BankAccount first{"Ayan", 100000}, second{"Dias", 50000};
    cout << "Account 1: " << first.owner << "\nBalance: " << first.balance
         << "\nAccount 2: " << second.owner << "\nBalance: " << second.balance
         << "\nTransfer: 30000\n";
    cout << (transfer(&first, &second, 30000) ? "Transfer successful!\n" : "Transfer failed!\n");
    printAccount(first);
    printAccount(second);
}

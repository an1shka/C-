#include <iostream>
using namespace std;

void addMoney(int* balance, int amount) {
    if (balance != nullptr && amount > 0) *balance += amount;
}

int main() {
    int balance = 5000;
    cout << "Before: " << balance << '\n';
    addMoney(&balance, 2000);
    cout << "After: " << balance << '\n';
}

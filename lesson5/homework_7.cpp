#include <iostream>
using namespace std;

int main() {
    const int correctPin = 4321;
    int pin, attempts = 0;
    bool granted = false;
    do {
        cout << "Enter PIN: ";
        cin >> pin;
        ++attempts;
        if (pin == correctPin) {
            granted = true;
            cout << "Access granted!\nAttempts: " << attempts << '\n';
        } else {
            cout << "Wrong PIN!\n";
        }
    } while (!granted && attempts < 3);
    if (!granted) cout << "Account blocked!\n";
}

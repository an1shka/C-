#include <iostream>
using namespace std;
int main() {
    int day, month, year; cin >> day >> month >> year;
    if (year <= 0 || month < 1 || month > 12 || day < 1) { cout << "INVALID\n"; return 0; }
    int daysInMonth;
    switch (month) {
        case 4: case 6: case 9: case 11: daysInMonth = 30; break;
        case 2: {
            bool leap = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
            daysInMonth = leap ? 29 : 28;
            break;
        }
        default: daysInMonth = 31;
    }
    cout << (day <= daysInMonth ? "VALID" : "INVALID") << '\n';
}

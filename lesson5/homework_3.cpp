#include <iostream>
using namespace std;

int main() {
    long long salary, increase, total = 0;
    int years;
    cin >> salary >> increase >> years;
    if (salary < 0 || increase < 0 || years < 0) {
        cout << "Invalid input\n";
        return 0;
    }
    for (int year = 1; year <= years; ++year) {
        salary += increase;
        total += salary;
        cout << "Year " << year << ": " << salary << '\n';
    }
    cout << "Total: " << total << '\n';
}

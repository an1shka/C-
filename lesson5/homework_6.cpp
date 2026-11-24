#include <iostream>
using namespace std;

int main() {
    long long currentMoney, target, monthlySavings;
    cin >> currentMoney >> target >> monthlySavings;
    if (currentMoney < 0 || target <= 0 || monthlySavings <= 0) {
        cout << "Invalid input\n";
        return 0;
    }
    int months = 0;
    while (currentMoney < target) {
        currentMoney += monthlySavings;
        ++months;
    }
    cout << "Months: " << months << "\nFinal money: " << currentMoney << '\n';
}

#include <iostream>
using namespace std;

int main() {
    long long number;
    cin >> number;
    if (number <= 0) {
        cout << "Invalid input\n";
        return 0;
    }
    int digits = 0, sum = 0, maxDigit = 0, oddDigits = 0;
    while (number > 0) {
        int digit = static_cast<int>(number % 10);
        ++digits;
        sum += digit;
        if (digit > maxDigit) maxDigit = digit;
        if (digit % 2 != 0) ++oddDigits;
        number /= 10;
    }
    cout << "Digits: " << digits << "\nSum: " << sum
         << "\nMax digit: " << maxDigit << "\nOdd digits: " << oddDigits << '\n';
}

#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    if (a <= 0 || b <= 0 || a > b) {
        cout << "Invalid input\n";
        return 0;
    }
    int count = 0, sum = 0;
    cout << "Numbers:";
    for (int number = a; number <= b; ++number) {
        if (number % 3 == 0 && number % 5 != 0) {
            cout << ' ' << number;
            ++count;
            sum += number;
        }
    }
    cout << "\nCount: " << count << "\nSum: " << sum << '\n';
}

#include <iostream>
using namespace std;

int main() {
    long long number;
    cin >> number;
    if (number <= 0) {
        cout << "Invalid input\n";
        return 0;
    }
    long long reversed = 0;
    while (number > 0) {
        reversed = reversed * 10 + number % 10;
        number /= 10;
    }
    cout << reversed << '\n';
}

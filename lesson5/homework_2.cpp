#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    bool prime = n > 1;
    for (int divisor = 2; divisor <= n / divisor && prime; ++divisor) {
        if (n % divisor == 0) prime = false;
    }
    cout << (prime ? "Prime number" : "Not prime") << '\n';
}

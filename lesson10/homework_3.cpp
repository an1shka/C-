#include <iostream>
using namespace std;
int main() {
    long long n; cin >> n;
    if (n <= 0) { cout << "Invalid input\n"; return 0; }
    long long outerIterations = 0, innerIterations = 0;
    for (long long i = 1; i < n; i *= 2) {
        ++outerIterations;
        innerIterations += n;
        if (i > n / 2) break;
    }
    cout << "Outer iterations: " << outerIterations
         << "\nInner body executions: " << innerIterations
         << "\nComplexity: O(n log n)\n";
}

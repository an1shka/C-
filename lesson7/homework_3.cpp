#include <iostream>
using namespace std;

void swapNumbers(int* a, int* b) {
    if (a == nullptr || b == nullptr) return;
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

int main() {
    int a = 10, b = 25;
    cout << "Before:\na = " << a << "\nb = " << b << '\n';
    swapNumbers(&a, &b);
    cout << "After:\na = " << a << "\nb = " << b << '\n';
}

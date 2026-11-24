#include <iostream>
using namespace std;

void swapNumbers(int* a, int* b) {
    if (a == nullptr || b == nullptr) return;
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

int main() {
    int x = 10, y = 25;
    cout << "Before:\nx = " << x << "\ny = " << y << '\n';
    swapNumbers(&x, &y);
    cout << "After:\nx = " << x << "\ny = " << y << '\n';
}

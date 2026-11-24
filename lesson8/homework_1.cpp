#include <iostream>
using namespace std;

int calculate(int a, int b, char operation) {
    if (operation == '+') return a + b;
    if (operation == '-') return a - b;
    return a * b;
}
int main() {
    int a, b; char operation;
    cin >> a >> b >> operation;
    if (operation != '+' && operation != '-' && operation != '*') cout << "Invalid operation\n";
    else cout << "Result: " << calculate(a, b, operation) << '\n';
}

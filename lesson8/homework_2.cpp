#include <iostream>
using namespace std;
void multiplyByTwo(int* number) { if (number != nullptr) *number *= 2; }
int main() {
    int number = 7;
    cout << "Before: " << number << '\n';
    multiplyByTwo(&number);
    cout << "After: " << number << '\n';
}

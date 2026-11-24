#include <iostream>
using namespace std;

int main() {
    int number = 45;
    int* ptr = &number;
    cout << "Number: " << number << "\nAddress: " << &number
         << "\nPointer: " << ptr << "\nValue by pointer: " << *ptr << '\n';
}

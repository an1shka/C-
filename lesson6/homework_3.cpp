#include <iostream>
using namespace std;

int main() {
    int first = 15, second = 30;
    int* ptr = &first;
    cout << *ptr << '\n';
    ptr = &second;
    cout << *ptr << '\n';
    *ptr = 80;
    cout << "First: " << first << "\nSecond: " << second << '\n';
}

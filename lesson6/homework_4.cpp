#include <iostream>
using namespace std;

int main() {
    int* ptr = nullptr;
    if (ptr == nullptr) cout << "Pointer is empty\n";
    int age = 21;
    ptr = &age;
    if (ptr != nullptr) cout << "Age: " << *ptr << '\n';
}

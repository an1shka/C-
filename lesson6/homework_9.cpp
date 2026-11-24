#include <iostream>
using namespace std;

int main() {
    int* products = new int(10);
    cout << "Initial products: " << *products << '\n';
    *products += 5;
    cout << "After adding: " << *products << '\n';
    *products -= 3;
    cout << "After selling: " << *products << '\n';
    delete products;
    products = nullptr;
}

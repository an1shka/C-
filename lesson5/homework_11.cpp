#include <iostream>
using namespace std;

int main() {
    int height;
    cin >> height;
    if (height < 1 || height > 20) {
        cout << "Invalid input\n";
        return 0;
    }
    for (int row = 1; row <= height; ++row) {
        for (int column = 0; column < row; ++column) cout << '*';
        cout << '\n';
    }
}

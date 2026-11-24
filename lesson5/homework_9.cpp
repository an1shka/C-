#include <iostream>
using namespace std;

int main() {
    int rows, columns;
    cin >> rows >> columns;
    if (rows < 1 || rows > 10 || columns < 1 || columns > 9) {
        cout << "Invalid input\n";
        return 0;
    }
    for (int row = 0; row < rows; ++row) {
        for (int number = 1; number <= columns; ++number) cout << number;
        cout << '\n';
    }
}

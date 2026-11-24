#include <iostream>
using namespace std;

int main() {
    int height, width;
    cin >> height >> width;
    if (height < 1 || height > 20 || width < 1 || width > 20) {
        cout << "Invalid input\n";
        return 0;
    }
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) cout << '*';
        cout << '\n';
    }
}

#include <iostream>
using namespace std;

int main() {
    int score = 50;
    int* ptr = &score;
    cout << "Before: " << score << '\n';
    *ptr = 100;
    cout << "After: " << score << '\n';
}

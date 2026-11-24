#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> numbers = {7, 2, 6, 1, 5};
    int comparisons = 0, swaps = 0;
    for (int i = 0; i + 1 < static_cast<int>(numbers.size()); ++i) {
        ++comparisons;
        if (numbers[i] > numbers[i + 1]) {
            int temporary = numbers[i]; numbers[i] = numbers[i + 1]; numbers[i + 1] = temporary;
            ++swaps;
        }
    }
    cout << "After one pass:";
    for (int number : numbers) cout << ' ' << number;
    cout << "\nComparisons: " << comparisons << "\nSwaps: " << swaps << '\n';
}

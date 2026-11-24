#include <array>
#include <iostream>
using namespace std;
int findMaximum(const array<int, 6>& numbers) {
    int maximum = numbers[0];
    for (int number : numbers) if (number > maximum) maximum = number;
    return maximum;
}
int main() {
    array<int, 6> numbers = {4, 12, 7, 25, 9, 15};
    cout << "Maximum: " << findMaximum(numbers) << '\n';
}

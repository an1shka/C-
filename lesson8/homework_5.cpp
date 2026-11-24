#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> grades = {80, 90, 75, 100, 85};
    int sum = 0;
    cout << "Grades:";
    for (int grade : grades) { cout << ' ' << grade; sum += grade; }
    cout << "\nSum: " << sum << "\nAverage: " << static_cast<double>(sum) / grades.size() << '\n';
}

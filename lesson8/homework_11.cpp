#include <iostream>
#include <set>
using namespace std;
int main() {
    set<int> uniqueNumbers;
    for (int i = 0; i < 10; ++i) { int number; cin >> number; uniqueNumbers.insert(number); }
    cout << "Unique:";
    for (int number : uniqueNumbers) cout << ' ' << number;
    cout << "\nCount: " << uniqueNumbers.size() << '\n';
}

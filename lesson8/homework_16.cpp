#include <iostream>
#include <stack>
using namespace std;
int main() {
    stack<int> numbers;
    for (int i = 0; i < 5; ++i) { int number; cin >> number; numbers.push(number); }
    cout << "Output:";
    while (!numbers.empty()) { cout << ' ' << numbers.top(); numbers.pop(); }
    cout << '\n';
}

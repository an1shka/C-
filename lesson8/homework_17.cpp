#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    unordered_map<int, int> counts;
    for (int i = 0; i < 8; ++i) { int number; cin >> number; ++counts[number]; }
    for (const auto& item : counts) cout << item.first << ": " << item.second << " times\n";
}

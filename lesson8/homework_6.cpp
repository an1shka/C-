#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    vector<string> names;
    for (int i = 0; i < 5; ++i) { string name; cin >> name; names.push_back(name); }
    for (const string& name : names) cout << name << '\n';
    cout << "Total students: " << names.size() << '\n';
}

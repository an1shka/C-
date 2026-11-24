#include <iostream>
#include <set>
#include <string>
using namespace std;
int main() {
    set<string> users = {"Ayan", "Dana", "Miras"};
    string name; cin >> name;
    cout << (users.count(name) ? "User found" : "User not found") << '\n';
}

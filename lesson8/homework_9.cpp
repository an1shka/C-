#include <iostream>
#include <map>
#include <string>
using namespace std;
int main() {
    map<string, string> contacts = {
        {"Ayan", "87011234567"}, {"Dana", "87021234567"},
        {"Miras", "87031234567"}, {"Ali", "87041234567"}
    };
    string name; cin >> name;
    auto found = contacts.find(name);
    if (found == contacts.end()) cout << "Contact not found\n";
    else cout << "Phone: " << found->second << '\n';
}

#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;
int main() {
    unordered_set<string> logins = {"ayan123", "dana19", "miras18", "ali777", "asel01"};
    string login; cin >> login;
    if (logins.count(login)) cout << "Login already taken\n";
    else { logins.insert(login); cout << "Registration successful\n"; }
}

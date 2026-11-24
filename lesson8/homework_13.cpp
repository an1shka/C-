#include <iostream>
#include <queue>
#include <string>
using namespace std;
int main() {
    queue<string> clients;
    for (const char* name : {"Ayan", "Dana", "Miras", "Ali", "Asel"}) clients.push(name);
    cout << "First client: " << clients.front() << '\n';
    cout << clients.front() << " served\n";
    clients.pop();
    cout << "Next client: " << clients.front() << "\nClients left: " << clients.size() << '\n';
}

#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() {
    stack<string> history;
    for (const char* action : {"Open", "Edit", "Save", "Close"}) history.push(action);
    cout << "Last action: " << history.top() << "\nUndo action\n";
    history.pop();
    cout << "Now last: " << history.top() << '\n';
}

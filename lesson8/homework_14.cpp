#include <iostream>
#include <queue>
using namespace std;
void processOrder(queue<int>& orders) {
    if (orders.empty()) { cout << "No orders\n"; return; }
    cout << "Processed order: " << orders.front() << '\n';
    orders.pop();
}
int main() {
    queue<int> orders;
    orders.push(101); orders.push(102); orders.push(103);
    processOrder(orders); processOrder(orders);
    if (!orders.empty()) cout << "Order left: " << orders.front() << '\n';
}

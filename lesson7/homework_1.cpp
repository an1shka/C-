#include <iostream>
using namespace std;

long long calculateTotal(int price, int quantity) { return 1LL * price * quantity; }
long long applyDiscount(long long total, int discount) {
    return total - total * discount / 100;
}

int main() {
    int price, quantity, discount;
    cin >> price >> quantity >> discount;
    if (price < 0 || quantity < 0 || discount < 0 || discount > 100) {
        cout << "Invalid input\n";
        return 0;
    }
    long long total = calculateTotal(price, quantity);
    cout << "Total: " << total << "\nAfter discount: "
         << applyDiscount(total, discount) << '\n';
}

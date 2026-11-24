#include <iostream>
#include <string>
using namespace std;

struct Product { string name; int price; int quantity; };
bool sellProduct(Product* product, int amount) {
    if (product == nullptr || amount <= 0 || amount > product->quantity) return false;
    product->quantity -= amount;
    return true;
}
void addStock(Product& product, int amount) { if (amount > 0) product.quantity += amount; }
long long calculateStockValue(Product product) { return 1LL * product.price * product.quantity; }

int main() {
    Product product{"Keyboard", 15000, 10};
    cout << "Product: " << product.name << "\nPrice: " << product.price
         << "\nQuantity: " << product.quantity << "\nSell: 3\n";
    if (!sellProduct(&product, 3)) cout << "Not enough products!\n";
    cout << "Remaining: " << product.quantity << "\nAdd stock: 5\n";
    addStock(product, 5);
    cout << "Remaining: " << product.quantity << "\nTotal stock value: "
         << calculateStockValue(product) << '\n';
}

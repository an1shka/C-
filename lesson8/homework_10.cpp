#include <iostream>
#include <map>
#include <string>
using namespace std;
void printProducts(const map<string, int>& products) {
    for (const auto& product : products) cout << product.first << ": " << product.second << '\n';
}
int main() {
    map<string, int> products = {{"Apple",500},{"Milk",700},{"Bread",250},{"Tea",1200},{"Rice",900}};
    printProducts(products);
    string name; cin >> name;
    auto found = products.find(name);
    if (found == products.end()) cout << "Product not found\n";
    else cout << "Price: " << found->second << '\n';
}

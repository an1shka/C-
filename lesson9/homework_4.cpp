#include <iomanip>
#include <iostream>
using namespace std;
int main() {
    double cart; int vip, promo, deliveryType;
    cin >> cart >> vip >> promo >> deliveryType;
    if (cart <= 0 || (vip != 0 && vip != 1) || (promo != 0 && promo != 1) ||
        (deliveryType != 1 && deliveryType != 2)) {
        cout << "Invalid input\n"; return 0;
    }
    int discountPercent = 0;
    if (vip == 1 && cart >= 5000) discountPercent = 10;
    if (promo == 1 && cart >= 15000) discountPercent = 15;
    double discount = cart * discountPercent / 100.0;
    double normalDelivery = cart >= 20000 ? 0 : 1500;
    double delivery = deliveryType == 1 ? normalDelivery : normalDelivery + 1000;
    cout << fixed << setprecision(2) << "Applied discount: " << discountPercent
         << "%\nDiscount amount: " << discount << " KZT\nDelivery: " << delivery
         << " KZT\nFinal total: " << cart - discount + delivery << " KZT\n";
}

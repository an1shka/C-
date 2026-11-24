#include <iomanip>
#include <iostream>
using namespace std;
int main() {
    int tariff, hour, vip, airport; double distance;
    cin >> tariff >> distance >> hour >> vip >> airport;
    if (tariff < 1 || tariff > 3 || distance <= 0 || hour < 0 || hour > 23 ||
        (vip != 0 && vip != 1) || (airport != 0 && airport != 1)) {
        cout << "Invalid input\n"; return 0;
    }
    double boarding = 0, perKm = 0;
    switch (tariff) {
        case 1: boarding = 700; perKm = 110; break;
        case 2: boarding = 1300; perKm = 170; break;
        case 3: boarding = 2500; perKm = 280; break;
    }
    double base = boarding + distance * perKm;
    double night = (hour >= 22 || hour <= 5) ? base * 0.25 : 0;
    double afterNight = base + night;
    double vipDiscount = vip == 1 ? afterNight * 0.10 : 0;
    double airportFee = airport == 1 ? 2000 : 0;
    cout << fixed << setprecision(2) << "Base price: " << base << " KZT\nNight surcharge: "
         << night << " KZT\nVIP discount: " << vipDiscount << " KZT\nFinal price: "
         << afterNight - vipDiscount + airportFee << " KZT\n";
}

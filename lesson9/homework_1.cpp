#include <iostream>
using namespace std;
int main() {
    int ent, english, olympiad; double gpa;
    cin >> ent >> english >> gpa >> olympiad;
    if (ent < 0 || ent > 140 || english < 0 || english > 100 || gpa < 0 || gpa > 4 || (olympiad != 0 && olympiad != 1)) {
        cout << "Invalid input\n"; return 0;
    }
    if (ent < 70 || english < 50) cout << "Admission denied\n";
    else if (ent >= 120 && english >= 80 && gpa >= 3.5) cout << "Admission: APPROVED\nScholarship: 100%\n";
    else if ((ent >= 100 && gpa >= 3.0) || (olympiad == 1 && ent >= 90)) cout << "Admission: APPROVED\nScholarship: 50%\n";
    else cout << "Admission without scholarship\n";
}

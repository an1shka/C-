#include <iomanip>
#include <iostream>
using namespace std;
int main() {
    int age, score, experience, term;
    double income, currentPayments, loan;
    cin >> age >> income >> currentPayments >> score >> experience >> loan >> term;
    if (income <= 0 || currentPayments < 0 || loan <= 0 || experience < 0 ||
        score < 300 || score > 850 || (term != 12 && term != 24 && term != 36)) {
        cout << "Invalid input\n"; return 0;
    }
    double payment = loan / term;
    if (age < 21 || age > 65) cout << "DENIED\nReason: Invalid age\n";
    else if (score < 650) cout << "DENIED\nReason: Credit score below 650\n";
    else if (experience < 6) cout << "DENIED\nReason: Work experience below 6 months\n";
    else if (loan > income * 10) cout << "DENIED\nReason: Loan amount is too high\n";
    else if (currentPayments + payment > income * 0.40) cout << "DENIED\nReason: Payment load exceeds 40%\n";
    else {
        const char* risk = score >= 750 ? "LOW RISK" : (score >= 700 ? "MEDIUM RISK" : "HIGH RISK");
        cout << fixed << setprecision(2) << "Status: APPROVED\nRisk level: " << risk
             << "\nEstimated payment: " << payment << " KZT\n";
    }
}

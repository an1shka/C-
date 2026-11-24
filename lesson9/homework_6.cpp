#include <iostream>
#include <string>
using namespace std;
int main() {
    int role, action, blocked, managerApproval, sameDepartment, twoFactor;
    cin >> role >> action >> blocked >> managerApproval >> sameDepartment >> twoFactor;
    bool flagsValid = (blocked == 0 || blocked == 1) && (managerApproval == 0 || managerApproval == 1) &&
                      (sameDepartment == 0 || sameDepartment == 1) && (twoFactor == 0 || twoFactor == 1);
    if (role < 1 || role > 4 || action < 1 || action > 4 || !flagsValid) {
        cout << "Invalid input\n"; return 0;
    }
    bool allowed = false; string reason;
    if (blocked == 1) reason = "User is blocked";
    else if (role == 1) {
        if (action == 4 && twoFactor == 0) reason = "2FA confirmation required";
        else allowed = true;
    } else if (role == 2) {
        if (action == 1 || action == 2) allowed = true;
        else if (action == 3 && managerApproval == 1) allowed = true;
        else if (action == 3) reason = "Manager approval required";
        else reason = "Insufficient permissions";
    } else if (role == 3) {
        if (action == 1) allowed = true;
        else if (action == 2 && sameDepartment == 1) allowed = true;
        else if (action == 2) reason = "Same department required";
        else reason = "Insufficient permissions";
    } else {
        if (action == 1) allowed = true;
        else reason = "Insufficient permissions";
    }
    if (allowed) cout << "ACCESS GRANTED\n";
    else cout << "ACCESS DENIED\nReason: " << reason << '\n';
}

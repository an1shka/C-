#include <iostream>
#include <string>
using namespace std;

struct Employee { string name; int salary; int experience; };
void increaseSalary(Employee* employee, int bonus) {
    if (employee != nullptr && bonus > 0 && employee->experience >= 3) employee->salary += bonus;
}
void printEmployee(Employee employee) {
    cout << "Employee: " << employee.name << "\nSalary: " << employee.salary
         << "\nExperience: " << employee.experience << '\n';
}

int main() {
    Employee employee{"Dias", 250000, 4};
    printEmployee(employee);
    cout << "Bonus: 50000\n";
    increaseSalary(&employee, 50000);
    cout << "Updated salary: " << employee.salary << '\n';
}

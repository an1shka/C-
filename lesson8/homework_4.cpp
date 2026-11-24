#include <iostream>
#include <string>
using namespace std;
struct Student { string name; int age; int grade; };
void updateGrade(Student* student, int newGrade) {
    if (student != nullptr && newGrade >= 0 && newGrade <= 100) student->grade = newGrade;
}
int main() {
    Student student{"Ayan", 18, 70};
    cout << "Student: " << student.name << "\nAge: " << student.age
         << "\nGrade before: " << student.grade << '\n';
    updateGrade(&student, 95);
    cout << "Grade after: " << student.grade << '\n';
}

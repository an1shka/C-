#include <iostream>
#include <string>
using namespace std;

struct Student { string name; int grade1; int grade2; };
double calculateAverage(Student student) { return (student.grade1 + student.grade2) / 2.0; }
void updateGrade(Student* student, int newGrade) {
    if (student != nullptr && newGrade >= 0 && newGrade <= 100) student->grade2 = newGrade;
}
void printStudent(Student student) {
    cout << "Student: " << student.name << "\nGrade 1: " << student.grade1
         << "\nGrade 2: " << student.grade2 << "\nAverage: "
         << calculateAverage(student) << '\n';
}

int main() {
    Student student{"Ayan", 70, 80};
    printStudent(student);
    updateGrade(&student, 100);
    cout << "New grade: 100\n";
    printStudent(student);
}

#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Student { string name; int age; int grade; };
void printStudents(const vector<Student>& students) {
    for (const Student& student : students)
        cout << student.name << ", " << student.age << " years, " << student.grade << '\n';
}
int main() {
    vector<Student> students = {{"Ayan",18,85},{"Dana",19,95},{"Miras",18,78}};
    printStudents(students);
    const Student* best = &students[0];
    for (const Student& student : students) if (student.grade > best->grade) best = &student;
    cout << "Best grade: " << best->name << " (" << best->grade << ")\n";
}

#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int age;
    int grade;
};

int main() {
    Student student = {"Ali", 18, 75};
    Student* ptr = &student;
    cout << "Name: " << ptr->name << "\nAge: " << ptr->age
         << "\nGrade: " << ptr->grade << '\n';
    ptr->grade = 95;
    cout << "After update:\nName: " << ptr->name << "\nAge: " << ptr->age
         << "\nGrade: " << ptr->grade << '\n';
}

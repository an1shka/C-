#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

struct Student{
        string name;
        int age;
        double gpa;
        string group;
    };

int main() {
    // vector<int> grades = {90,85,100};

    // map<string, int> students = {
    //     {"Ali", 90},
    //     {"Danya", 85},
    // };

    // set<int> uniquenumbers = {5,2,5,3};

    // cout << grades[0] << endl;
    // cout << students["Ali"] << endl;

    // for(int x : uniquenumbers) {
    //     cout << x << " ";
    // }
    // cout << endl;

    //2. struct
    // Student student1;
    // student1.name = "Ali";
    // student1.age = 20;
    // student1.gpa = 3.8;
    // student1.group = "A";

    // Student s1 = {"Ali", 19, 3.5};
    // Student s2 = {"Yana", 20, 3.9};
    // Student s3 = {"Lera", 18, 4.0};

    // cout << "Name:" << s1.name << endl;
    // cout << "Age:" << s2.age << endl;
    // cout << "GPA:" << s3.gpa << endl;
    

    // vector<Student> students;

    // students.push_back({"Ali", 19, 90});
    // students.push_back({"qwerty", 20, 85});
    // students.push_back({"Lera", 18, 100});

    // Student s1;

    // cout << "Enter name: ";
    // cin >> s1.name;
    // cout << "Enter age: ";
    // cin >> s1.age;
    // cout << "Enter grade: ";
    // cin >> s1.gpa;

    // cout << "\nStudent: " << s1.name << "\n";
    // cout << "Age: " << s1.age << "\n";
    // cout << "Grade: " << s1.gpa << "\n\n";

    // struct Car {
    //     string brand;
    //     long long price;
    // };

    // Car car1 = {"Toyota", 10000000};
    // Car car2 = {"Hyundai", 12000000};

    // cout << car1.brand << " - " << car1.price << "\n";
    // cout << car2.brand << " - " << car2.price << "\n\n";

    // if (car1.price > car2.price) {
    //     cout << "More expensive: " << car1.brand << "\n\n";
    // } else if (car2.price > car1.price) {
    //     cout << "More expensive: " << car2.brand << "\n\n";
    // } else {
    //     cout << "Prices are equal\n\n";
    // }

    // string password;
    // cout << "Enter password: ";
    // cin >> password;

    // size_t len = password.length();

    // if (len < 6) {
    //     cout << "Weak password\n\n";
    // } else if (len >= 6 && len <= 9) {
    //     cout << "Normal password\n\n";
    // } else {
    //     cout << "Strong password\n\n";
    // }

    // // Очищаем буфер после cin перед getline
    // cin.ignore();

    // string text, word;

    // cout << "Enter text: ";
    // getline(cin, text);
    // cout << "Search word: ";
    // cin >> word;

    // if (text.find(word) != string::npos) {
    //     cout << "Word found\n\n";
    // } else {
    //     cout << "Word not found\n\n";
    // }

    // cin.ignore();

    // struct Book {
    //     string title;
    //     string author;
    // };

    // vector<Book> library = {
    //     {"Clean Code", "Robert Martin"},
    //     {"Harry Potter", "J.K. Rowling"},
    //     {"The Hobbit", "J.R.R. Tolkien"}
    // };

    // string searchTitle;
    // cout << "Enter book title: ";
    // getline(cin, searchTitle);

    // bool found = false;
    // for (const auto& book : library) {
    //     if (book.title == searchTitle) {
    //         cout << "\nBook found!\n";
    //         cout << "Title: " << book.title << "\n";
    //         cout << "Author: " << book.author << "\n";
    //         found = true;
    //         break;
    //     }
    // }

    // if (!found) {
    //     cout << "Book not found\n";
    // };


    //3
    // vector<int> numbers3 = {3, 8, 12, 5, 7, 20, 11};
    // cout << "Even numbers:";
    // int count3 = 0;
    // for (auto it = numbers3.begin(); it != numbers3.end(); ++it) {
    //     if (*it % 2 == 0) {
    //         cout << " " << *it;
    //         count3++;
    //     }
    // }
    // cout << "\nCount: " << count3 << "\n\n";

    //4
    // vector<int> numbers4 = {2, 4, 6, 8, 10};
    // cout << "Before:";
    // for (auto it = numbers4.begin(); it != numbers4.end(); ++it) {
    //     cout << " " << *it;
    // }
    // cout << "\n";
    // for (auto it = numbers4.begin(); it != numbers4.end(); ++it) {
    //     *it *= 2;
    // }
    // cout << "After:";
    // for (auto it = numbers4.begin(); it != numbers4.end(); ++it) {
    //     cout << " " << *it;
    // }
    // cout << "\n\n";

    //5
    // string word;
    // cout << "Enter word: ";
    // cin >> word;
    // int vowelsCount = 0;
    // for (auto it = word.begin(); it != word.end(); ++it) {
    //     char ch = *it;
    //     if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
    //         vowelsCount++;
    //     }
    // }
    // cout << "Vowels: " << vowelsCount << "\n\n";

    //6
    // vector<int> numbers6 = {15, 3, 27, 8, 42, 11};
    // auto it6 = numbers6.begin();
    // int minVal = *it6;
    // int maxVal = *it6;
    // ++it6;
    // for (; it6 != numbers6.end(); ++it6) {
    //     if (*it6 < minVal) {
    //         minVal = *it6;
    //     }
    //     if (*it6 > maxVal) {
    //         maxVal = *it6;
    //     }
    // }
    // cout << "Minimum: " << minVal << "\n";
    // cout << "Maximum: " << maxVal << "\n\n";

    //7
    // set<int> numbers7 = {7, 2, 20, 15, 7, 2};
    // cout << "Elements:";
    // for (auto it = numbers7.begin(); it != numbers7.end(); ++it) {
    //     cout << " " << *it;
    // }
    // cout << "\n";
    // cout << "Unique count: " << numbers7.size() << "\n";
    // int sumGreater10 = 0;
    // for (auto it = numbers7.begin(); it != numbers7.end(); ++it) {
    //     if (*it > 10) {
    //         sumGreater10 += *it;
    //     }
    // }
    // cout << "Sum greater than 10: " << sumGreater10 << "\n\n";

    //8
    // map<string, int> students8 = {
    //     {"Ali", 82},
    //     {"Madi", 91},
    //     {"Dana", 94},
    //     {"Ruslan", 68}
    // };
    // cout << "All students:\n";
    // for (auto it = students8.begin(); it != students8.end(); ++it) {
    //     cout << it->first << ": " << it->second << "\n";
    // }
    // cout << "High grades:\n";
    // int highCount8 = 0;
    // for (auto it = students8.begin(); it != students8.end(); ++it) {
    //     if (it->second >= 90) {
    //         cout << it->first << ": " << it->second << "\n";
    //         highCount8++;
    //     }
    // }
    // cout << "Count: " << highCount8 << "\n\n";

    //9
    // vector<int> numbers9 = {5, -2, 8, -7, 0, 12, -1};
    // cout << "Before:";
    // for (auto it = numbers9.begin(); it != numbers9.end(); ++it) {
    //     cout << " " << *it;
    // }
    // cout << "\n";
    // for (auto it = numbers9.begin(); it != numbers9.end(); ) {
    //     if (*it < 0) {
    //         it = numbers9.erase(it);
    //     } else {
    //         ++it;
    //     }
    // }
    // cout << "After:";
    // for (auto it = numbers9.begin(); it != numbers9.end(); ++it) {
    //     cout << " " << *it;
    // }
    // cout << "\n\n";

    //10
    struct Student10 {
        string name;
        int age;
        int grade;
    };
    vector<Student10> students10 = {
        {"Ali", 19, 85},
        {"Madi", 20, 91},
        {"Dana", 18, 97},
        {"Arman", 21, 78}
    };
    cout << "All students:\n";
    for (auto it = students10.begin(); it != students10.end(); ++it) {
        cout << it->name << " - " << it->age << " - " << it->grade << "\n";
    }
    auto bestIt = students10.begin();
    int count90 = 0;
    for (auto it = students10.begin(); it != students10.end(); ++it) {
        if (it->grade > bestIt->grade) {
            bestIt = it;
        }
        if (it->grade >= 90) {
            count90++;
        }
    }
    cout << "Best student:\n";
    cout << "Name: " << bestIt->name << "\n";
    cout << "Age: " << bestIt->age << "\n";
    cout << "Grade: " << bestIt->grade << "\n";
    cout << "Students with grade >= 90: " << count90 << "\n";


    return 0;
}


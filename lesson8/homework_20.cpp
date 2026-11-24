#include <iostream>
#include <map>
#include <string>
using namespace std;

void showBooks(const map<string, int>& books) {
    for (const auto& book : books) cout << book.first << ": " << book.second << '\n';
}
void findBook(const map<string, int>& books, const string& title) {
    auto found = books.find(title);
    if (found == books.end()) cout << "Book not found\n";
    else cout << title << ": " << found->second << '\n';
}
void takeBook(map<string, int>& books, const string& title) {
    auto found = books.find(title);
    if (found == books.end()) cout << "Book not found\n";
    else if (found->second == 0) cout << "No copies available\n";
    else { --found->second; cout << "Book issued\n"; }
}
void returnBook(map<string, int>& books, const string& title) {
    auto found = books.find(title);
    if (found == books.end()) cout << "Book not found\n";
    else { ++found->second; cout << "Book returned\n"; }
}
int main() {
    map<string, int> books = {{"Clean Code",2},{"The Hobbit",1},{"Harry Potter",0}};
    int choice;
    do {
        cout << "===== LIBRARY =====\n1. Show books\n2. Find book\n3. Take book\n4. Return book\n5. Exit\n";
        cin >> choice;
        if (choice == 1) showBooks(books);
        else if (choice >= 2 && choice <= 4) {
            cin.ignore();
            string title; getline(cin, title);
            if (choice == 2) findBook(books, title);
            else if (choice == 3) takeBook(books, title);
            else returnBook(books, title);
        } else if (choice != 5) cout << "Unknown command\n";
    } while (choice != 5);
}

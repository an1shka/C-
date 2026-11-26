#pragma once

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace practice {

namespace warmup {

class Student {
public:
    std::string name;
    int age;
    std::string group;
    double averageGrade;

    Student(std::string n, int a, std::string g, double grade)
        : name(std::move(n)), age(a), group(std::move(g)), averageGrade(grade) {}

    void showInfo() const {
        std::cout << name << ", " << age << " years, group " << group
                  << ", grade " << averageGrade << '\n';
    }
    void study() const { std::cout << name << " is studying.\n"; }
    double getScholarship() const { return averageGrade >= 90 ? 5000 : averageGrade >= 75 ? 2500 : 0; }
};

class BankAccount {
    std::string owner_;
    std::string number_;
    double balance_;
public:
    BankAccount(std::string owner, std::string number, double balance)
        : owner_(std::move(owner)), number_(std::move(number)), balance_(balance) {
        if (balance < 0) throw std::invalid_argument("Initial balance cannot be negative.");
    }
    void deposit(double amount) {
        if (amount <= 0) throw std::invalid_argument("Deposit must be positive.");
        balance_ += amount;
    }
    void withdraw(double amount) {
        if (amount <= 0 || amount > balance_) throw std::invalid_argument("Invalid withdrawal amount.");
        balance_ -= amount;
    }
    void transfer(BankAccount& other, double amount) {
        withdraw(amount);
        other.deposit(amount);
    }
    void showBalance() const { std::cout << owner_ << " (" << number_ << "): " << balance_ << '\n'; }
};

class Product {
public:
    std::string name;
    double price;
    int quantity;
    std::string category;

    Product(std::string n, double p, int q, std::string c)
        : name(std::move(n)), price(p), quantity(q), category(std::move(c)) {}
    double getTotalPrice() const { return price * quantity; }
    void sell(int count) {
        if (count <= 0 || count > quantity) throw std::invalid_argument("Invalid stock quantity.");
        quantity -= count;
    }
    void addStock(int count) {
        if (count <= 0) throw std::invalid_argument("Quantity must be positive.");
        quantity += count;
    }
    void showProductInfo() const {
        std::cout << name << " | " << category << " | " << price << " x " << quantity << '\n';
    }
};

inline void demo() {
    std::cout << "\n--- 1. Classes, objects, constructors ---\n";
    std::vector<Student> students{
        {"Anna", 19, "A1", 91}, {"Ivan", 20, "A1", 78}, {"Mira", 18, "B2", 85},
        {"Oleg", 21, "B2", 68}, {"Lena", 19, "A1", 96}
    };
    for (const auto& student : students) {
        student.showInfo();
        student.study();
        std::cout << "Scholarship: " << student.getScholarship() << '\n';
    }
    const auto best = std::max_element(students.begin(), students.end(),
        [](const Student& a, const Student& b) { return a.averageGrade < b.averageGrade; });
    std::cout << "Best student: " << best->name << '\n';

    BankAccount first("Anna", "1001", 1000), second("Ivan", "1002", 250);
    first.deposit(100);
    first.transfer(second, 300);
    first.showBalance();
    second.showBalance();

    std::vector<Product> products;
    for (int i = 1; i <= 10; ++i)
        products.emplace_back("Product " + std::to_string(i), i * 10.0, i % 6, "General");
    const auto expensive = std::max_element(products.begin(), products.end(),
        [](const Product& a, const Product& b) { return a.price < b.price; });
    double stockValue = 0;
    std::cout << "Most expensive: " << expensive->name << "\nLow stock:";
    for (const auto& product : products) {
        stockValue += product.getTotalPrice();
        if (product.quantity < 5) std::cout << ' ' << product.name;
    }
    std::cout << "\nTotal stock value: " << stockValue << '\n';
}
} // namespace warmup

namespace encapsulation {

class Wallet {
    double balance_ = 0;
    std::vector<std::string> history_;
public:
    double balance() const { return balance_; }
    const std::vector<std::string>& history() const { return history_; }
    void addMoney(double amount) {
        if (amount <= 0) throw std::invalid_argument("Amount must be positive.");
        balance_ += amount;
        history_.push_back("Added " + std::to_string(amount));
    }
    void spendMoney(double amount) {
        if (amount <= 0 || amount > balance_) throw std::invalid_argument("Insufficient funds or invalid amount.");
        balance_ -= amount;
        history_.push_back("Spent " + std::to_string(amount));
    }
};

class GradeBook {
    std::string student_;
    std::vector<int> grades_;
public:
    explicit GradeBook(std::string student) : student_(std::move(student)) {}
    const std::vector<int>& grades() const { return grades_; }
    void addGrade(int grade) {
        if (grade < 0 || grade > 100) throw std::invalid_argument("Grade must be from 0 to 100.");
        grades_.push_back(grade);
    }
    void removeGrade(std::size_t index) {
        if (index >= grades_.size()) throw std::out_of_range("Grade index does not exist.");
        grades_.erase(grades_.begin() + static_cast<std::ptrdiff_t>(index));
    }
    double average() const {
        if (grades_.empty()) return 0;
        int total = 0;
        for (int grade : grades_) total += grade;
        return static_cast<double>(total) / static_cast<double>(grades_.size());
    }
    bool isFailing() const { return average() < 50; }
    int minimum() const { return grades_.empty() ? 0 : *std::min_element(grades_.begin(), grades_.end()); }
    int maximum() const { return grades_.empty() ? 0 : *std::max_element(grades_.begin(), grades_.end()); }
    const std::string& student() const { return student_; }
};

class Thermostat {
    double current_;
    double minimum_;
    double maximum_;
    bool enabled_ = true;
public:
    Thermostat(double current, double minimum, double maximum)
        : current_(current), minimum_(minimum), maximum_(maximum) {
        if (minimum > maximum || current < minimum || current > maximum)
            throw std::invalid_argument("Invalid thermostat temperature range.");
    }
    double currentTemperature() const { return current_; }
    double minTemperature() const { return minimum_; }
    double maxTemperature() const { return maximum_; }
    bool isEnabled() const { return enabled_; }
    void setEnabled(bool enabled) { enabled_ = enabled; }
    void setTemperature(double value) {
        if (!enabled_) throw std::logic_error("Thermostat is disabled.");
        if (value < minimum_ || value > maximum_) throw std::out_of_range("Temperature is outside allowed range.");
        current_ = value;
    }
};

inline void demo() {
    std::cout << "\n--- 2. Encapsulation ---\n";
    Wallet wallet;
    wallet.addMoney(1000);
    wallet.spendMoney(250);
    std::cout << "Wallet balance: " << wallet.balance() << ", operations: " << wallet.history().size() << '\n';
    GradeBook grades("Mira");
    grades.addGrade(70);
    grades.addGrade(82);
    grades.addGrade(94);
    std::cout << grades.student() << " average: " << grades.average()
              << ", min: " << grades.minimum() << ", max: " << grades.maximum()
              << ", failing: " << (grades.isFailing() ? "yes" : "no") << '\n';
    Thermostat thermostat(21, 10, 30);
    thermostat.setTemperature(23);
    std::cout << "Thermostat: " << thermostat.currentTemperature() << " C\n";
}
} // namespace encapsulation

namespace inheritance {

class Employee {
protected:
    std::string name_;
    int age_;
    double salary_;
public:
    Employee(std::string name, int age, double salary)
        : name_(std::move(name)), age_(age), salary_(salary) {}
    virtual ~Employee() = default;
    virtual void showInfo() const {
        std::cout << name_ << ", age " << age_ << ", salary " << salary_ << '\n';
    }
    virtual void work() const { std::cout << name_ << " is working.\n"; }
};
class Manager : public Employee {
    std::string department_;
    int employees_;
public:
    Manager(std::string n, int a, double s, std::string d, int e)
        : Employee(std::move(n), a, s), department_(std::move(d)), employees_(e) {}
    void work() const override { std::cout << name_ << " manages " << employees_ << " people in " << department_ << ".\n"; }
};
class Developer : public Employee {
    std::string language_;
public:
    Developer(std::string n, int a, double s, std::string language)
        : Employee(std::move(n), a, s), language_(std::move(language)) {}
    void work() const override { std::cout << name_ << " writes " << language_ << " code.\n"; }
};
class Designer : public Employee {
    std::string tool_;
public:
    Designer(std::string n, int a, double s, std::string tool)
        : Employee(std::move(n), a, s), tool_(std::move(tool)) {}
    void work() const override { std::cout << name_ << " designs with " << tool_ << ".\n"; }
};
class Tester : public Employee {
    std::string type_;
public:
    Tester(std::string n, int a, double s, std::string type)
        : Employee(std::move(n), a, s), type_(std::move(type)) {}
    void work() const override { std::cout << name_ << " performs " << type_ << " testing.\n"; }
};

class Vehicle {
protected:
    std::string brand_, model_;
    int year_, speed_ = 0;
public:
    Vehicle(std::string brand, std::string model, int year)
        : brand_(std::move(brand)), model_(std::move(model)), year_(year) {}
    virtual ~Vehicle() = default;
    virtual void start() { std::cout << brand_ << ' ' << model_ << " started.\n"; }
    virtual void stop() { speed_ = 0; std::cout << "Stopped.\n"; }
    virtual void move() { speed_ = 30; std::cout << "Moving at " << speed_ << " km/h.\n"; }
    virtual void feature() const { std::cout << "Standard vehicle.\n"; }
};
class Car : public Vehicle {
public:
    Car(std::string b, std::string m, int y) : Vehicle(std::move(b), std::move(m), y) {}
    void feature() const override { std::cout << "Car: 5 seats.\n"; }
};
class Motorcycle : public Vehicle {
public:
    Motorcycle(std::string b, std::string m, int y) : Vehicle(std::move(b), std::move(m), y) {}
    void feature() const override { std::cout << "Motorcycle: two wheels.\n"; }
};
class Bus : public Vehicle {
public:
    Bus(std::string b, std::string m, int y) : Vehicle(std::move(b), std::move(m), y) {}
    void feature() const override { std::cout << "Bus carries passengers.\n"; }
};
class Truck : public Vehicle {
public:
    Truck(std::string b, std::string m, int y) : Vehicle(std::move(b), std::move(m), y) {}
    void feature() const override { std::cout << "Truck carries cargo.\n"; }
};
class Bicycle : public Vehicle {
public:
    Bicycle(std::string b, std::string m, int y) : Vehicle(std::move(b), std::move(m), y) {}
    void feature() const override { std::cout << "Bicycle uses no fuel.\n"; }
};

class StoreProduct {
protected:
    std::string name_;
    double price_;
public:
    StoreProduct(std::string name, double price) : name_(std::move(name)), price_(price) {}
    virtual ~StoreProduct() = default;
    virtual void show() const { std::cout << name_ << ": " << price_ << '\n'; }
};
class FoodProduct : public StoreProduct {
    std::string expiry_;
public:
    FoodProduct(std::string n, double p, std::string expiry) : StoreProduct(std::move(n), p), expiry_(std::move(expiry)) {}
    void show() const override { StoreProduct::show(); std::cout << "Expires: " << expiry_ << '\n'; }
};
class ElectronicProduct : public StoreProduct {
    int warrantyMonths_;
public:
    ElectronicProduct(std::string n, double p, int months) : StoreProduct(std::move(n), p), warrantyMonths_(months) {}
    void show() const override { StoreProduct::show(); std::cout << "Warranty: " << warrantyMonths_ << " months\n"; }
};
class ClothingProduct : public StoreProduct {
    std::string size_;
public:
    ClothingProduct(std::string n, double p, std::string size) : StoreProduct(std::move(n), p), size_(std::move(size)) {}
    void show() const override { StoreProduct::show(); std::cout << "Size: " << size_ << '\n'; }
};
class BookProduct : public StoreProduct {
    std::string author_;
public:
    BookProduct(std::string n, double p, std::string author) : StoreProduct(std::move(n), p), author_(std::move(author)) {}
    void show() const override { StoreProduct::show(); std::cout << "Author: " << author_ << '\n'; }
};

class Animal {
public:
    virtual ~Animal() = default;
    virtual void makeSound() const { std::cout << "Animal sound\n"; }
    virtual void eat() const { std::cout << "Animal eats\n"; }
    virtual void move() const { std::cout << "Animal moves\n"; }
};
#define PRACTICE_ANIMAL(Type, Sound, Food, Motion) \
class Type : public Animal { \
public: \
    void makeSound() const override { std::cout << Sound << '\n'; } \
    void eat() const override { std::cout << Food << '\n'; } \
    void move() const override { std::cout << Motion << '\n'; } \
};
PRACTICE_ANIMAL(Dog, "Woof!", "Dog eats meat.", "Dog runs.")
PRACTICE_ANIMAL(Cat, "Meow!", "Cat eats fish.", "Cat walks.")
PRACTICE_ANIMAL(Bird, "Chirp!", "Bird eats seeds.", "Bird flies.")
PRACTICE_ANIMAL(Fish, "Blub!", "Fish eats plankton.", "Fish swims.")
PRACTICE_ANIMAL(Cow, "Moo!", "Cow eats grass.", "Cow walks.")
PRACTICE_ANIMAL(Lion, "Roar!", "Lion eats meat.", "Lion runs.")
#undef PRACTICE_ANIMAL

class Payment {
public:
    virtual ~Payment() = default;
    virtual void processPayment(double amount) const { std::cout << "Payment: " << amount << '\n'; }
};
#define PRACTICE_PAYMENT(Type, Label) \
class Type : public Payment { \
public: void processPayment(double amount) const override { std::cout << Label << " payment: " << amount << '\n'; } \
};
PRACTICE_PAYMENT(CashPayment, "Cash")
PRACTICE_PAYMENT(CardPayment, "Card")
PRACTICE_PAYMENT(PayPalPayment, "PayPal")
PRACTICE_PAYMENT(CryptoPayment, "Crypto")
#undef PRACTICE_PAYMENT

class Notification {
public:
    virtual ~Notification() = default;
    virtual void send(const std::string& message) const { std::cout << message << '\n'; }
};
#define PRACTICE_NOTIFICATION(Type, Label) \
class Type : public Notification { \
public: void send(const std::string& message) const override { std::cout << Label << ": " << message << '\n'; } \
};
PRACTICE_NOTIFICATION(EmailNotification, "Email")
PRACTICE_NOTIFICATION(SmsNotification, "SMS")
PRACTICE_NOTIFICATION(TelegramNotification, "Telegram")
PRACTICE_NOTIFICATION(PushNotification, "Push")
#undef PRACTICE_NOTIFICATION

inline void demo() {
    std::cout << "\n--- 3. Inheritance and virtual methods ---\n";
    std::vector<std::unique_ptr<Employee>> employees;
    employees.emplace_back(new Manager("Alex", 40, 5000, "IT", 8));
    employees.emplace_back(new Developer("Sam", 28, 4000, "C++"));
    employees.emplace_back(new Designer("Rita", 31, 3500, "Figma"));
    employees.emplace_back(new Tester("Max", 27, 3200, "manual"));
    for (const auto& e : employees) { e->showInfo(); e->work(); }
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    vehicles.emplace_back(new Bus("Volvo", "7900", 2022));
    vehicles.emplace_back(new Bicycle("Trek", "FX", 2024));
    for (const auto& v : vehicles) v->feature();
    std::vector<std::unique_ptr<StoreProduct>> goods;
    goods.emplace_back(new FoodProduct("Milk", 2.5, "2026-12-01"));
    goods.emplace_back(new ElectronicProduct("Headphones", 75, 24));
    goods.emplace_back(new ClothingProduct("Jacket", 80, "M"));
    goods.emplace_back(new BookProduct("C++", 30, "B. Stroustrup"));
    for (const auto& p : goods) p->show();
    std::vector<std::unique_ptr<Animal>> animals;
    animals.emplace_back(new Dog()); animals.emplace_back(new Cat()); animals.emplace_back(new Bird());
    animals.emplace_back(new Fish()); animals.emplace_back(new Cow()); animals.emplace_back(new Lion());
    for (const auto& a : animals) { a->makeSound(); a->eat(); a->move(); }
    std::vector<std::unique_ptr<Payment>> payments;
    payments.emplace_back(new CashPayment()); payments.emplace_back(new CardPayment());
    payments.emplace_back(new PayPalPayment()); payments.emplace_back(new CryptoPayment());
    for (const auto& p : payments) p->processPayment(50);
    std::vector<std::unique_ptr<Notification>> notifications;
    notifications.emplace_back(new EmailNotification()); notifications.emplace_back(new SmsNotification());
    notifications.emplace_back(new TelegramNotification()); notifications.emplace_back(new PushNotification());
    for (const auto& n : notifications) n->send("Practice notification");
}
} // namespace inheritance

namespace abstraction {

class Shape {
public:
    virtual ~Shape() = default;
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void showInfo() const {
        std::cout << "Area: " << calculateArea() << ", perimeter: " << calculatePerimeter() << '\n';
    }
};
class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) { if (r <= 0) throw std::invalid_argument("Radius must be positive."); }
    double calculateArea() const override { return 3.141592653589793 * r_ * r_; }
    double calculatePerimeter() const override { return 2 * 3.141592653589793 * r_; }
};
class Rectangle : public Shape {
protected:
    double width_, height_;
public:
    Rectangle(double w, double h) : width_(w), height_(h) {
        if (w <= 0 || h <= 0) throw std::invalid_argument("Sides must be positive.");
    }
    double calculateArea() const override { return width_ * height_; }
    double calculatePerimeter() const override { return 2 * (width_ + height_); }
};
class Square : public Rectangle {
public:
    explicit Square(double side) : Rectangle(side, side) {}
};
class Triangle : public Shape {
    double a_, b_, c_;
public:
    Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {
        if (a <= 0 || b <= 0 || c <= 0 || a + b <= c || a + c <= b || b + c <= a)
            throw std::invalid_argument("Invalid triangle sides.");
    }
    double calculateArea() const override {
        const double s = calculatePerimeter() / 2;
        return std::sqrt(s * (s - a_) * (s - b_) * (s - c_));
    }
    double calculatePerimeter() const override { return a_ + b_ + c_; }
};

class Delivery {
protected:
    std::string address_;
    double weight_;
public:
    Delivery(std::string address, double weight) : address_(std::move(address)), weight_(weight) {
        if (weight <= 0) throw std::invalid_argument("Weight must be positive.");
    }
    virtual ~Delivery() = default;
    virtual double calculateDeliveryPrice() const = 0;
    virtual void deliver() const { std::cout << "Delivering to " << address_ << " for " << calculateDeliveryPrice() << '\n'; }
};
#define PRACTICE_DELIVERY(Type, Formula) \
class Type : public Delivery { \
public: Type(std::string address, double weight) : Delivery(std::move(address), weight) {} \
    double calculateDeliveryPrice() const override { return Formula; } \
};
PRACTICE_DELIVERY(CarDelivery, 5 + weight_ * 2)
PRACTICE_DELIVERY(BikeDelivery, 3 + weight_ * 1.5)
PRACTICE_DELIVERY(DroneDelivery, 10 + weight_ * 4)
PRACTICE_DELIVERY(CourierDelivery, 7 + weight_ * 2.5)
#undef PRACTICE_DELIVERY

class BankAccount {
protected:
    std::string owner_;
    double balance_;
public:
    BankAccount(std::string owner, double balance) : owner_(std::move(owner)), balance_(balance) {
        if (balance < 0) throw std::invalid_argument("Balance cannot be negative.");
    }
    virtual ~BankAccount() = default;
    virtual double calculateInterest() const = 0;
    virtual bool withdraw(double amount) = 0;
    double balance() const { return balance_; }
};
class SavingsAccount : public BankAccount {
public:
    using BankAccount::BankAccount;
    double calculateInterest() const override { return balance_ * 0.05; }
    bool withdraw(double amount) override {
        if (amount <= 0 || amount > balance_) return false;
        balance_ -= amount; return true;
    }
};
class BusinessAccount : public BankAccount {
public:
    using BankAccount::BankAccount;
    double calculateInterest() const override { return balance_ * 0.02; }
    bool withdraw(double amount) override {
        if (amount <= 0 || amount > balance_ + 1000) return false;
        balance_ -= amount; return true;
    }
};
class StudentAccount : public BankAccount {
public:
    using BankAccount::BankAccount;
    double calculateInterest() const override { return balance_ * 0.03; }
    bool withdraw(double amount) override {
        if (amount <= 0 || amount > balance_ || amount > 500) return false;
        balance_ -= amount; return true;
    }
};

inline void demo() {
    std::cout << "\n--- 4. Abstract classes ---\n";
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(new Circle(3));
    shapes.emplace_back(new Rectangle(4, 5));
    shapes.emplace_back(new Square(4));
    shapes.emplace_back(new Triangle(3, 4, 5));
    auto largest = std::max_element(shapes.begin(), shapes.end(),
        [](const auto& a, const auto& b) { return a->calculateArea() < b->calculateArea(); });
    for (const auto& shape : shapes) shape->showInfo();
    std::cout << "Largest area: " << (*largest)->calculateArea() << '\n';
    std::vector<std::unique_ptr<Delivery>> deliveries;
    deliveries.emplace_back(new CarDelivery("Main street", 4));
    deliveries.emplace_back(new BikeDelivery("Park avenue", 2));
    deliveries.emplace_back(new DroneDelivery("Lake road", 1));
    deliveries.emplace_back(new CourierDelivery("Oak street", 3));
    for (const auto& d : deliveries) d->deliver();
    std::vector<std::unique_ptr<BankAccount>> accounts;
    accounts.emplace_back(new SavingsAccount("Anna", 1000));
    accounts.emplace_back(new BusinessAccount("Shop", 3000));
    accounts.emplace_back(new StudentAccount("Ivan", 600));
    for (const auto& a : accounts)
        std::cout << "Interest: " << a->calculateInterest() << ", withdrawal accepted: " << a->withdraw(100) << '\n';
}
} // namespace abstraction

namespace interfaces {

inline void writeSaveFile(const std::string& path, const std::string& data) {
    std::ofstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("Could not open save file: " + path);
    file << data;
    if (!file) throw std::runtime_error("Could not write save file: " + path);
}
inline std::string readSaveFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("Could not open save file: " + path);
    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

struct IPrintable { virtual ~IPrintable() = default; virtual void print() const = 0; };
struct IScannable { virtual ~IScannable() = default; virtual void scan() const = 0; };
struct IFaxable { virtual ~IFaxable() = default; virtual void sendFax() const = 0; };
class Printer : public IPrintable { public: void print() const override { std::cout << "Printing...\n"; } };
class Scanner : public IScannable { public: void scan() const override { std::cout << "Scanning...\n"; } };
class MultifunctionDevice : public IPrintable, public IScannable, public IFaxable {
public:
    void print() const override { std::cout << "MFD printing...\n"; }
    void scan() const override { std::cout << "MFD scanning...\n"; }
    void sendFax() const override { std::cout << "MFD sending fax...\n"; }
};
struct IDrive { virtual ~IDrive() = default; virtual void drive() const = 0; };
struct IFly { virtual ~IFly() = default; virtual void fly() const = 0; };
struct ISwim { virtual ~ISwim() = default; virtual void swim() const = 0; };
class Car : public IDrive { public: void drive() const override { std::cout << "Car drives.\n"; } };
class Airplane : public IDrive, public IFly {
public: void drive() const override { std::cout << "Airplane taxis.\n"; } void fly() const override { std::cout << "Airplane flies.\n"; }
};
class Boat : public ISwim { public: void swim() const override { std::cout << "Boat sails.\n"; } };
class Duck : public IFly, public ISwim {
public: void fly() const override { std::cout << "Duck flies.\n"; } void swim() const override { std::cout << "Duck swims.\n"; }
};
class SuperVehicle : public IDrive, public IFly, public ISwim {
public:
    void drive() const override { std::cout << "SuperVehicle drives.\n"; }
    void fly() const override { std::cout << "SuperVehicle flies.\n"; }
    void swim() const override { std::cout << "SuperVehicle swims.\n"; }
};
struct ISaveable { virtual ~ISaveable() = default; virtual void save() = 0; virtual void load() = 0; };
class User : public ISaveable {
    std::string data_;
public:
    explicit User(std::string data) : data_(std::move(data)) {}
    void save() override { writeSaveFile("user.save", data_); }
    void load() override { data_ = readSaveFile("user.save"); std::cout << "User loaded: " << data_ << '\n'; }
};
class Game : public ISaveable {
    std::string data_;
public:
    explicit Game(std::string data) : data_(std::move(data)) {}
    void save() override { writeSaveFile("game.save", data_); }
    void load() override { data_ = readSaveFile("game.save"); std::cout << "Game loaded: " << data_ << '\n'; }
};
class Document : public ISaveable {
    std::string data_;
public:
    explicit Document(std::string data) : data_(std::move(data)) {}
    void save() override { writeSaveFile("document.save", data_); }
    void load() override { data_ = readSaveFile("document.save"); std::cout << "Document loaded: " << data_ << '\n'; }
};
class Settings : public ISaveable {
    std::string data_;
public:
    explicit Settings(std::string data) : data_(std::move(data)) {}
    void save() override { writeSaveFile("settings.save", data_); }
    void load() override { data_ = readSaveFile("settings.save"); std::cout << "Settings loaded: " << data_ << '\n'; }
};

inline void demo() {
    std::cout << "\n--- 5. Interfaces ---\n";
    Printer printer; printer.print();
    Scanner scanner; scanner.scan();
    MultifunctionDevice mfd; mfd.print(); mfd.scan(); mfd.sendFax();
    Airplane plane; plane.drive(); plane.fly();
    Duck duck; duck.fly(); duck.swim();
    User user("Alex"); Game game("Level 4"); Document document("Report"); Settings settings("Dark mode");
    std::vector<ISaveable*> saveables{&user, &game, &document, &settings};
    for (auto* item : saveables) { item->save(); item->load(); }
}
} // namespace interfaces

namespace mixed {

struct IStudy { virtual ~IStudy() = default; virtual void study() const = 0; };
struct ITeach { virtual ~ITeach() = default; virtual void teach() const = 0; };
struct IManage { virtual ~IManage() = default; virtual void manage() const = 0; };
class Person {
    int id_;
    std::string name_;
    int age_;
public:
    Person(int id, std::string name, int age) : id_(id), name_(std::move(name)), age_(age) {}
    virtual ~Person() = default;
    virtual void showRole() const = 0;
    const std::string& name() const { return name_; }
};
class UniversityStudent : public Person, public IStudy {
public:
    using Person::Person;
    void showRole() const override { std::cout << name() << " is a student.\n"; }
    void study() const override { std::cout << name() << " studies.\n"; }
};
class Teacher : public Person, public ITeach {
public:
    using Person::Person;
    void showRole() const override { std::cout << name() << " is a teacher.\n"; }
    void teach() const override { std::cout << name() << " teaches.\n"; }
};
class Administrator : public Person, public IManage {
public:
    using Person::Person;
    void showRole() const override { std::cout << name() << " is an administrator.\n"; }
    void manage() const override { std::cout << name() << " manages the university.\n"; }
};

struct IBookable { virtual ~IBookable() = default; virtual void book() = 0; virtual void cancelBooking() = 0; };
struct IPayable { virtual ~IPayable() = default; virtual bool pay(double amount) = 0; };
struct ICleanable { virtual ~ICleanable() = default; virtual void clean() = 0; };
class Room : public IBookable, public IPayable, public ICleanable {
    int number_;
    double nightlyRate_;
    bool booked_ = false, occupied_ = false;
    std::string guest_;
public:
    Room(int number, double rate) : number_(number), nightlyRate_(rate) {
        if (rate <= 0) throw std::invalid_argument("Room price must be positive.");
    }
    virtual ~Room() = default;
    virtual std::string type() const = 0;
    void book() override {
        if (booked_ || occupied_) throw std::logic_error("Room is not available.");
        booked_ = true;
    }
    void cancelBooking() override {
        if (!booked_ || occupied_) throw std::logic_error("Booking cannot be cancelled.");
        booked_ = false;
    }
    void checkIn(const std::string& guest) {
        if (!booked_) throw std::logic_error("A reservation is required before check-in.");
        booked_ = false; occupied_ = true; guest_ = guest;
    }
    void checkOut() {
        if (!occupied_) throw std::logic_error("Room is not occupied.");
        occupied_ = false; guest_.clear();
    }
    double calculateStay(int nights) const {
        if (nights <= 0) throw std::invalid_argument("Night count must be positive.");
        return nightlyRate_ * nights;
    }
    bool pay(double amount) override {
        if (amount < 0) throw std::invalid_argument("Payment cannot be negative.");
        return amount > 0;
    }
    void clean() override { if (occupied_) throw std::logic_error("Cannot clean an occupied room."); std::cout << "Room " << number_ << " cleaned.\n"; }
    bool available() const { return !booked_ && !occupied_; }
};
class StandardRoom : public Room {
public: using Room::Room; std::string type() const override { return "Standard"; }
};
class LuxuryRoom : public Room {
public: using Room::Room; std::string type() const override { return "Luxury"; }
};
class FamilyRoom : public Room {
public: using Room::Room; std::string type() const override { return "Family"; }
};
class Guest {
    std::string name_;
public: explicit Guest(std::string name) : name_(std::move(name)) {} const std::string& name() const { return name_; }
};
class Booking {
    Guest guest_;
    Room& room_;
    int nights_;
public:
    Booking(Guest guest, Room& room, int nights)
        : guest_(std::move(guest)), room_(room), nights_(nights) {
        if (nights <= 0) throw std::invalid_argument("Night count must be positive.");
    }
    void reserve() { room_.book(); }
    void checkIn() { room_.checkIn(guest_.name()); }
    void checkOut() { room_.checkOut(); }
    double total() const { return room_.calculateStay(nights_); }
};
class Employee {
    std::string name_;
    std::string role_;
public:
    Employee(std::string name, std::string role)
        : name_(std::move(name)), role_(std::move(role)) {}
    void performDuty() const { std::cout << name_ << " works as " << role_ << ".\n"; }
};
class Hotel {
    std::vector<std::unique_ptr<Room>> rooms_;
public:
    void addRoom(std::unique_ptr<Room> room) { rooms_.push_back(std::move(room)); }
    Room* findAvailable() const {
        for (const auto& room : rooms_) if (room->available()) return room.get();
        return nullptr;
    }
};

struct IHealable { virtual ~IHealable() = default; virtual void heal(int amount) = 0; };
struct IUpgradeable { virtual ~IUpgradeable() = default; virtual void upgrade() = 0; };
struct ISpecialAbility { virtual ~ISpecialAbility() = default; virtual void specialAbility() const = 0; };
class Character : public IUpgradeable, public ISpecialAbility {
protected:
    std::string name_;
    int health_, damage_, level_ = 1;
public:
    Character(std::string name, int health, int damage)
        : name_(std::move(name)), health_(health), damage_(damage) {
        if (health <= 0 || damage <= 0) throw std::invalid_argument("Health and damage must be positive.");
    }
    virtual ~Character() = default;
    virtual void attack(Character& target) const = 0;
    virtual void takeDamage(int amount) {
        if (amount < 0) throw std::invalid_argument("Damage cannot be negative.");
        health_ = std::max(0, health_ - amount);
    }
    void upgrade() override { ++level_; damage_ += 2; }
    virtual void specialAbility() const override = 0;
    int health() const { return health_; }
    const std::string& name() const { return name_; }
};
class Warrior : public Character {
public:
    using Character::Character;
    void attack(Character& target) const override { std::cout << name_ << " performs a sword strike.\n"; target.takeDamage(damage_); }
    void specialAbility() const override { std::cout << name_ << " uses Shield Bash.\n"; }
};
class Mage : public Character {
public:
    using Character::Character;
    void attack(Character& target) const override { std::cout << name_ << " casts a spell.\n"; target.takeDamage(damage_ + 3); }
    void specialAbility() const override { std::cout << name_ << " uses Fireball.\n"; }
};
class Archer : public Character {
public:
    using Character::Character;
    void attack(Character& target) const override { std::cout << name_ << " shoots an arrow.\n"; target.takeDamage(damage_); }
    void specialAbility() const override { std::cout << name_ << " uses Multi-shot.\n"; }
};
class Healer : public Character, public IHealable {
public:
    using Character::Character;
    void attack(Character& target) const override { std::cout << name_ << " uses a staff.\n"; target.takeDamage(damage_); }
    void specialAbility() const override { std::cout << name_ << " uses Healing Light.\n"; }
    void heal(int amount) override {
        if (amount < 0) throw std::invalid_argument("Healing cannot be negative.");
        health_ += amount;
    }
};

inline void demo() {
    std::cout << "\n--- 6. Mixed OOP systems ---\n";
    std::vector<std::unique_ptr<Person>> people;
    people.emplace_back(new UniversityStudent(1, "Student A", 19));
    people.emplace_back(new UniversityStudent(2, "Student B", 20));
    people.emplace_back(new UniversityStudent(3, "Student C", 18));
    people.emplace_back(new Teacher(4, "Teacher A", 40));
    people.emplace_back(new Teacher(5, "Teacher B", 35));
    people.emplace_back(new Teacher(6, "Teacher C", 45));
    people.emplace_back(new Administrator(7, "Admin A", 50));
    people.emplace_back(new Administrator(8, "Admin B", 48));
    people.emplace_back(new Administrator(9, "Admin C", 55));
    for (const auto& p : people) p->showRole();
    dynamic_cast<IStudy&>(*people[0]).study();
    dynamic_cast<ITeach&>(*people[3]).teach();
    dynamic_cast<IManage&>(*people[6]).manage();

    Hotel hotel;
    hotel.addRoom(std::unique_ptr<Room>(new StandardRoom(101, 80)));
    hotel.addRoom(std::unique_ptr<Room>(new LuxuryRoom(201, 180)));
    hotel.addRoom(std::unique_ptr<Room>(new FamilyRoom(301, 130)));
    Room* room = hotel.findAvailable();
    Booking booking(Guest("Alex"), *room, 3);
    Employee employee("Morgan", "housekeeping");
    booking.reserve();
    booking.checkIn();
    std::cout << "Stay total: " << booking.total() << '\n';
    room->pay(booking.total());
    booking.checkOut();
    room->clean();
    employee.performDuty();

    std::vector<std::unique_ptr<Character>> party;
    party.emplace_back(new Warrior("Warrior", 100, 15));
    party.emplace_back(new Mage("Mage", 70, 18));
    party.emplace_back(new Archer("Archer", 80, 14));
    party.emplace_back(new Healer("Healer", 75, 10));
    for (std::size_t i = 0; i < party.size(); ++i) {
        party[i]->specialAbility();
        party[i]->attack(*party[(i + 1) % party.size()]);
    }
    dynamic_cast<Healer&>(*party[3]).heal(10);
    party[0]->upgrade();
    std::cout << party[0]->name() << " health after the round: " << party[0]->health() << '\n';
}
} // namespace mixed

inline void runAll() {
    warmup::demo();
    encapsulation::demo();
    inheritance::demo();
    abstraction::demo();
    interfaces::demo();
    mixed::demo();
}

} // namespace practice

#pragma once

#include <ctime>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace shop {

class IPayable {
public:
    virtual ~IPayable() = default;
    virtual bool pay(double amount) = 0;
};

class IDeliverable {
public:
    virtual ~IDeliverable() = default;
    virtual double calculateDeliveryPrice() const = 0;
    virtual std::string deliveryName() const = 0;
};

class IDiscountable {
public:
    virtual ~IDiscountable() = default;
    virtual double applyDiscount(double percent) const = 0;
};

class INotifiable {
public:
    virtual ~INotifiable() = default;
    virtual void notify(const std::string& message) const = 0;
};

class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual void printReceipt() const = 0;
};

class User {
    int id_;
    std::string name_;
    std::string email_;
    std::string password_;
    bool loggedIn_ = false;
public:
    User(int id, std::string name, std::string email, std::string password)
        : id_(id), name_(std::move(name)), email_(std::move(email)), password_(std::move(password)) {
        if (name_.empty() || email_.empty() || password_.empty())
            throw std::invalid_argument("Name, email, and password are required.");
    }
public:
    virtual ~User() = default;
    int id() const { return id_; }
    const std::string& name() const { return name_; }
    const std::string& email() const { return email_; }
    bool login(const std::string& password) {
        loggedIn_ = password == password_;
        return loggedIn_;
    }
    void logout() { loggedIn_ = false; }
    bool isLoggedIn() const { return loggedIn_; }
    virtual std::string role() const = 0;
    virtual bool canManageProducts() const { return false; }
};

class Admin : public User {
public:
    using User::User;
    std::string role() const override { return "Administrator"; }
    bool canManageProducts() const override { return true; }
};

class Customer : public User, public INotifiable {
public:
    using User::User;
    std::string role() const override { return "Customer"; }
    void notify(const std::string& message) const override {
        std::cout << "[Notification for " << name() << "] " << message << '\n';
    }
};

class Seller : public User {
public:
    using User::User;
    std::string role() const override { return "Seller"; }
    bool canManageProducts() const override { return true; }
};

class Product : public IDiscountable {
    int id_;
    std::string name_;
    double price_;
    std::string description_;
    int stock_;
protected:
    Product(int id, std::string name, double price, std::string description, int stock)
        : id_(id), name_(std::move(name)), price_(price), description_(std::move(description)), stock_(stock) {
        if (name_.empty() || price_ < 0 || stock_ < 0)
            throw std::invalid_argument("Product name, price, or stock is invalid.");
    }
public:
    virtual ~Product() = default;
    int id() const { return id_; }
    const std::string& name() const { return name_; }
    const std::string& description() const { return description_; }
    double price() const { return price_; }
    int stock() const { return stock_; }
    void setPrice(double price) {
        if (price < 0) throw std::invalid_argument("Price cannot be negative.");
        price_ = price;
    }
    void takeStock(int amount) {
        if (amount <= 0 || amount > stock_) throw std::invalid_argument("Invalid quantity or insufficient stock.");
        stock_ -= amount;
    }
    void restoreStock(int amount) {
        if (amount <= 0) throw std::invalid_argument("Quantity must be positive.");
        stock_ += amount;
    }
    double applyDiscount(double percent) const override {
        if (percent < 0 || percent > 100) throw std::invalid_argument("Discount must be from 0 to 100.");
        return calculatePrice() * (1.0 - percent / 100.0);
    }
    virtual double calculatePrice() const = 0;
    virtual std::string category() const = 0;
    virtual std::string detail() const = 0;
};

class Electronic : public Product {
    int warrantyMonths_;
public:
    Electronic(int id, std::string name, double price, std::string desc, int stock, int warranty)
        : Product(id, std::move(name), price, std::move(desc), stock), warrantyMonths_(warranty) {}
    std::string category() const override { return "Electronics"; }
    std::string detail() const override { return "Warranty: " + std::to_string(warrantyMonths_) + " months"; }
    double calculatePrice() const override { return price(); }
};

class Clothing : public Product {
    std::string size_;
public:
    Clothing(int id, std::string name, double price, std::string desc, int stock, std::string size)
        : Product(id, std::move(name), price, std::move(desc), stock), size_(std::move(size)) {}
    std::string category() const override { return "Clothing"; }
    std::string detail() const override { return "Size: " + size_; }
    double calculatePrice() const override { return price(); }
};

class Food : public Product {
    std::string expiryDate_;
public:
    Food(int id, std::string name, double price, std::string desc, int stock, std::string expiry)
        : Product(id, std::move(name), price, std::move(desc), stock), expiryDate_(std::move(expiry)) {}
    std::string category() const override { return "Food"; }
    std::string detail() const override { return "Best before: " + expiryDate_; }
    double calculatePrice() const override { return price(); }
};

class Book : public Product {
    std::string author_;
public:
    Book(int id, std::string name, double price, std::string desc, int stock, std::string author)
        : Product(id, std::move(name), price, std::move(desc), stock), author_(std::move(author)) {}
    std::string category() const override { return "Books"; }
    std::string detail() const override { return "Author: " + author_; }
    double calculatePrice() const override { return price(); }
};

struct CartItem {
    std::shared_ptr<Product> product;
    int quantity;
};

struct OrderItem {
    std::shared_ptr<Product> product;
    int quantity;
    double unitPrice;
};

class ShoppingCart {
    std::vector<CartItem> items_;
public:
    const std::vector<CartItem>& items() const { return items_; }
    void addProduct(const std::shared_ptr<Product>& product, int quantity) {
        if (!product || quantity <= 0 || quantity > product->stock())
            throw std::invalid_argument("Invalid product or quantity.");
        for (auto& item : items_) {
            if (item.product->id() == product->id()) {
                if (item.quantity + quantity > product->stock())
                    throw std::invalid_argument("Requested quantity exceeds available stock.");
                item.quantity += quantity;
                return;
            }
        }
        items_.push_back({product, quantity});
    }
    void removeProduct(int productId, int quantity) {
        for (auto it = items_.begin(); it != items_.end(); ++it) {
            if (it->product->id() == productId) {
                if (quantity <= 0 || quantity > it->quantity)
                    throw std::invalid_argument("Invalid quantity to remove.");
                it->quantity -= quantity;
                if (it->quantity == 0) items_.erase(it);
                return;
            }
        }
        throw std::invalid_argument("Product is not in the cart.");
    }
    void clear() { items_.clear(); }
    double calculateTotal(double discount = 0) const {
        double total = 0;
        for (const auto& item : items_)
            total += item.product->applyDiscount(discount) * item.quantity;
        return total;
    }
};

class Order : public INotifiable, public IPrintable {
public:
    enum class Status { Pending, Paid, Cancelled };
private:
    int id_;
    int customerId_;
    std::string customerName_;
    std::string date_;
    std::vector<OrderItem> items_;
    Status status_ = Status::Pending;
    double discount_;
    double deliveryCost_ = 0;
    std::string deliveryMethod_;
public:
    Order(int id, const Customer& customer, std::vector<CartItem> items, double discount)
        : id_(id), customerId_(customer.id()), customerName_(customer.name()),
          discount_(discount) {
        for (const auto& item : items)
            items_.push_back({item.product, item.quantity, item.product->calculatePrice()});
        std::time_t now = std::time(nullptr);
        std::tm* local = std::localtime(&now);
        std::ostringstream stream;
        if (local) stream << std::put_time(local, "%Y-%m-%d %H:%M");
        else stream << "date unavailable";
        date_ = stream.str();
    }
    int id() const { return id_; }
    int customerId() const { return customerId_; }
    Status status() const { return status_; }
    const std::vector<OrderItem>& items() const { return items_; }
    double calculateTotal() const {
        double total = 0;
        for (const auto& item : items_)
            total += item.unitPrice * (1.0 - discount_ / 100.0) * item.quantity;
        return total + deliveryCost_;
    }
    void setDelivery(const IDeliverable& delivery) {
        deliveryMethod_ = delivery.deliveryName();
        deliveryCost_ = delivery.calculateDeliveryPrice();
    }
    void markPaid() { status_ = Status::Paid; }
    void cancel() {
        if (status_ == Status::Cancelled) throw std::logic_error("Order is already cancelled.");
        status_ = Status::Cancelled;
    }
    std::string statusName() const {
        if (status_ == Status::Paid) return "Paid";
        if (status_ == Status::Cancelled) return "Cancelled";
        return "Pending";
    }
    void notify(const std::string& message) const override {
        std::cout << "[Order #" << id_ << "] " << message << '\n';
    }
    void printReceipt() const override {
        std::cout << "\n========== RECEIPT ==========\n"
                  << "Order: #" << id_ << "\nCustomer: " << customerName_
                  << "\nDate: " << date_ << "\n";
        for (const auto& item : items_)
            std::cout << item.product->name() << " x" << item.quantity << " = "
                      << item.unitPrice * (1.0 - discount_ / 100.0) * item.quantity << '\n';
        std::cout << "Discount: " << discount_ << "%\nDelivery (" << deliveryMethod_
                  << "): " << deliveryCost_ << "\nTotal: " << calculateTotal()
                  << "\nStatus: " << statusName() << "\n=============================\n";
    }
};

class Delivery : public IDeliverable {
protected:
    std::string address_;
    double weight_;
public:
    Delivery(std::string address, double weight) : address_(std::move(address)), weight_(weight) {
        if (address_.empty() || weight_ <= 0) throw std::invalid_argument("Address and positive weight are required.");
    }
    virtual ~Delivery() = default;
};

class CourierDelivery : public Delivery {
public:
    using Delivery::Delivery;
    double calculateDeliveryPrice() const override { return 5 + weight_ * 2; }
    std::string deliveryName() const override { return "Courier"; }
};
class PickupDelivery : public Delivery {
public:
    using Delivery::Delivery;
    double calculateDeliveryPrice() const override { return 0; }
    std::string deliveryName() const override { return "Pickup"; }
};
class DroneDelivery : public Delivery {
public:
    using Delivery::Delivery;
    double calculateDeliveryPrice() const override { return 12 + weight_ * 4; }
    std::string deliveryName() const override { return "Drone"; }
};

class PaymentMethod : public IPayable {
public:
    bool pay(double amount) override {
        if (amount < 0) throw std::invalid_argument("Payment amount cannot be negative.");
        std::cout << paymentName() << " payment accepted: " << amount << '\n';
        return true;
    }
    virtual std::string paymentName() const = 0;
};
class CardPayment : public PaymentMethod { public: std::string paymentName() const override { return "Card"; } };
class CashPayment : public PaymentMethod { public: std::string paymentName() const override { return "Cash"; } };
class OnlinePayment : public PaymentMethod { public: std::string paymentName() const override { return "Online"; } };

class Store {
    std::vector<std::unique_ptr<User>> users_;
    std::vector<std::shared_ptr<Product>> products_;
    std::vector<Order> orders_;
    ShoppingCart cart_;
    User* currentUser_ = nullptr;
    int nextUserId_ = 1;
    int nextProductId_ = 1;
    int nextOrderId_ = 1;

    static std::string readLine(const std::string& prompt) {
        std::cout << prompt;
        std::string value;
        if (!std::getline(std::cin, value)) throw std::runtime_error("Input stream closed.");
        return value;
    }
    static int readInt(const std::string& prompt) {
        const std::string text = readLine(prompt);
        std::size_t used = 0;
        int value = std::stoi(text, &used);
        if (used != text.size()) throw std::invalid_argument("Enter a whole number.");
        return value;
    }
    static double readDouble(const std::string& prompt) {
        const std::string text = readLine(prompt);
        std::size_t used = 0;
        double value = std::stod(text, &used);
        if (used != text.size() || !std::isfinite(value))
            throw std::invalid_argument("Enter a finite number.");
        return value;
    }
    std::shared_ptr<Product> findProduct(int id) const {
        for (const auto& product : products_) if (product->id() == id) return product;
        return nullptr;
    }
    Customer* currentCustomer() const { return dynamic_cast<Customer*>(currentUser_); }
    void listProducts() const {
        if (products_.empty()) { std::cout << "Catalog is empty.\n"; return; }
        std::cout << "\n--- PRODUCT CATALOG ---\n";
        for (const auto& p : products_)
            std::cout << '#' << p->id() << " | " << p->name() << " | " << p->category()
                      << " | " << p->price() << " | stock " << p->stock()
                      << " | " << p->detail() << " | " << p->description() << '\n';
    }
    void searchProducts() const {
        const std::string query = readLine("Search text: ");
        bool found = false;
        for (const auto& p : products_) {
            if (p->name().find(query) != std::string::npos ||
                p->category().find(query) != std::string::npos ||
                p->description().find(query) != std::string::npos) {
                std::cout << '#' << p->id() << ' ' << p->name() << " | " << p->price()
                          << " | stock " << p->stock() << '\n';
                found = true;
            }
        }
        if (!found) std::cout << "No matching products.\n";
    }
    void registerCustomer() {
        const std::string name = readLine("Name: ");
        const std::string email = readLine("Email: ");
        const std::string password = readLine("Password: ");
        for (const auto& user : users_)
            if (user->email() == email) throw std::invalid_argument("This email is already registered.");
        users_.emplace_back(new Customer(nextUserId_++, name, email, password));
        std::cout << "Registration successful. You can now log in.\n";
    }
    void login() {
        if (currentUser_) { std::cout << "Log out first.\n"; return; }
        const std::string email = readLine("Email: ");
        const std::string password = readLine("Password: ");
        for (const auto& user : users_) {
            if (user->email() == email) {
                if (!user->login(password)) throw std::invalid_argument("Incorrect password.");
                currentUser_ = user.get();
                std::cout << "Welcome, " << currentUser_->name() << " (" << currentUser_->role() << ").\n";
                return;
            }
        }
        throw std::invalid_argument("Account not found.");
    }
    void addProduct() {
        if (!currentUser_ || !currentUser_->canManageProducts())
            throw std::logic_error("Only an administrator or seller can manage products.");
        std::cout << "Type: 1 Electronics, 2 Clothing, 3 Food, 4 Book\n";
        const int type = readInt("Choose type: ");
        const std::string name = readLine("Product name: ");
        const double price = readDouble("Price: ");
        const std::string description = readLine("Description: ");
        const int stock = readInt("Stock quantity: ");
        switch (type) {
        case 1:
            products_.emplace_back(new Electronic(nextProductId_++, name, price, description, stock,
                                                   readInt("Warranty (months): ")));
            break;
        case 2:
            products_.emplace_back(new Clothing(nextProductId_++, name, price, description, stock,
                                                 readLine("Size: ")));
            break;
        case 3:
            products_.emplace_back(new Food(nextProductId_++, name, price, description, stock,
                                             readLine("Expiry date: ")));
            break;
        case 4:
            products_.emplace_back(new Book(nextProductId_++, name, price, description, stock,
                                             readLine("Author: ")));
            break;
        default: throw std::invalid_argument("Unknown product type.");
        }
        std::cout << "Product added.\n";
    }
    void deleteProduct() {
        if (!currentUser_ || !currentUser_->canManageProducts())
            throw std::logic_error("Only an administrator or seller can manage products.");
        const int id = readInt("Product ID to delete: ");
        for (auto it = products_.begin(); it != products_.end(); ++it) {
            if ((*it)->id() == id) {
                for (const auto& item : cart_.items())
                    if (item.product->id() == id)
                        throw std::logic_error("Remove the product from the cart before deleting it.");
                products_.erase(it);
                std::cout << "Product deleted.\n";
                return;
            }
        }
        throw std::invalid_argument("Product not found.");
    }
    void changePrice() {
        if (!currentUser_ || !currentUser_->canManageProducts())
            throw std::logic_error("Only an administrator or seller can manage products.");
        const int id = readInt("Product ID: ");
        auto product = findProduct(id);
        if (!product) throw std::invalid_argument("Product not found.");
        product->setPrice(readDouble("New price: "));
        std::cout << "Price updated.\n";
    }
    void addToCart() {
        Customer* customer = currentCustomer();
        if (!customer || !customer->isLoggedIn())
            throw std::logic_error("Log in as a customer before using the cart.");
        const int id = readInt("Product ID: ");
        auto product = findProduct(id);
        if (!product) throw std::invalid_argument("Product not found.");
        cart_.addProduct(product, readInt("Quantity: "));
        std::cout << "Added to cart. Total: " << cart_.calculateTotal() << '\n';
    }
    void showCart() const {
        if (cart_.items().empty()) { std::cout << "Cart is empty.\n"; return; }
        for (const auto& item : cart_.items())
            std::cout << '#' << item.product->id() << ' ' << item.product->name()
                      << " x" << item.quantity << " = " << item.product->price() * item.quantity << '\n';
        std::cout << "Subtotal: " << cart_.calculateTotal() << '\n';
    }
    void removeFromCart() {
        Customer* customer = currentCustomer();
        if (!customer || !customer->isLoggedIn())
            throw std::logic_error("Log in as a customer before using the cart.");
        showCart();
        if (cart_.items().empty()) return;
        cart_.removeProduct(readInt("Product ID: "), readInt("Quantity to remove: "));
        std::cout << "Cart updated.\n";
    }
    std::unique_ptr<Delivery> chooseDelivery() {
        std::cout << "Delivery: 1 Courier, 2 Pickup, 3 Drone\n";
        const int option = readInt("Choose delivery: ");
        const std::string address = readLine("Delivery address (or pickup location): ");
        const double weight = readDouble("Parcel weight in kg: ");
        switch (option) {
        case 1: return std::unique_ptr<Delivery>(new CourierDelivery(address, weight));
        case 2: return std::unique_ptr<Delivery>(new PickupDelivery(address, weight));
        case 3: return std::unique_ptr<Delivery>(new DroneDelivery(address, weight));
        default: throw std::invalid_argument("Unknown delivery method.");
        }
    }
    std::unique_ptr<PaymentMethod> choosePayment() {
        std::cout << "Payment: 1 Card, 2 Cash, 3 Online\n";
        switch (readInt("Choose payment: ")) {
        case 1: return std::unique_ptr<PaymentMethod>(new CardPayment());
        case 2: return std::unique_ptr<PaymentMethod>(new CashPayment());
        case 3: return std::unique_ptr<PaymentMethod>(new OnlinePayment());
        default: throw std::invalid_argument("Unknown payment method.");
        }
    }
    void checkout() {
        Customer* customer = currentCustomer();
        if (!customer || !customer->isLoggedIn())
            throw std::logic_error("Log in as a customer before checkout.");
        if (cart_.items().empty()) throw std::logic_error("Cannot checkout an empty cart.");
        double discount = readDouble("Discount percent (0-100): ");
        if (discount < 0 || discount > 100) throw std::invalid_argument("Discount must be from 0 to 100.");

        Order order(nextOrderId_++, *customer, cart_.items(), discount);
        std::unique_ptr<Delivery> delivery = chooseDelivery();
        order.setDelivery(*delivery);
        std::cout << "Order total: " << order.calculateTotal() << '\n';
        std::unique_ptr<PaymentMethod> payment = choosePayment();

        std::vector<CartItem> taken;
        try {
            for (const auto& item : cart_.items()) {
                item.product->takeStock(item.quantity);
                taken.push_back(item);
            }
            if (!payment->pay(order.calculateTotal())) throw std::runtime_error("Payment was declined.");
        } catch (...) {
            for (const auto& item : taken) item.product->restoreStock(item.quantity);
            throw;
        }
        order.markPaid();
        order.printReceipt();
        order.notify("Your order has been placed.");
        orders_.push_back(std::move(order));
        cart_.clear();
    }
    void orderHistory() const {
        if (!currentUser_) throw std::logic_error("Log in to view order history.");
        bool found = false;
        for (const auto& order : orders_) {
            if (order.customerId() == currentUser_->id()) {
                order.printReceipt();
                found = true;
            }
        }
        if (!found) std::cout << "No orders yet.\n";
    }
    void cancelOrder() {
        Customer* customer = currentCustomer();
        if (!customer || !customer->isLoggedIn())
            throw std::logic_error("Log in as a customer to cancel an order.");
        const int id = readInt("Order ID: ");
        for (auto& order : orders_) {
            if (order.id() == id && order.customerId() == customer->id()) {
                if (order.status() != Order::Status::Paid)
                    throw std::logic_error("Only paid orders can be cancelled.");
                order.cancel();
                for (const auto& item : order.items()) item.product->restoreStock(item.quantity);
                order.notify("Order cancelled; items returned to stock.");
                return;
            }
        }
        throw std::invalid_argument("Order not found for this customer.");
    }
    void logout() {
        if (!currentUser_) { std::cout << "No user is logged in.\n"; return; }
        currentUser_->logout();
        std::cout << currentUser_->name() << " logged out.\n";
        currentUser_ = nullptr;
        cart_.clear();
    }
    void seedData() {
        users_.emplace_back(new Admin(nextUserId_++, "Store Admin", "admin@shop.local", "admin123"));
        users_.emplace_back(new Seller(nextUserId_++, "Store Seller", "seller@shop.local", "seller123"));
        users_.emplace_back(new Customer(nextUserId_++, "Demo Customer", "customer@shop.local", "customer123"));
        products_.emplace_back(new Electronic(nextProductId_++, "Wireless Headphones", 89.99,
                                               "Bluetooth headphones", 12, 24));
        products_.emplace_back(new Clothing(nextProductId_++, "T-Shirt", 19.50, "Cotton shirt", 20, "M"));
        products_.emplace_back(new Food(nextProductId_++, "Coffee", 12.75, "Roasted coffee beans", 30, "2027-01-01"));
        products_.emplace_back(new Book(nextProductId_++, "C++ Basics", 34.00, "Programming guide", 8, "A. Author"));
    }
public:
    Store() { seedData(); }
    void run() {
        bool running = true;
        while (running) {
            std::cout << "\n========== ONLINE STORE ==========\n"
                      << "User: " << (currentUser_ ? currentUser_->name() + " (" + currentUser_->role() + ")" : "Guest")
                      << "\n1 Register customer  2 Login  3 Logout\n"
                      << "4 Catalog  5 Search  6 Add to cart  7 View cart  8 Remove from cart\n"
                      << "9 Checkout  10 Order history  11 Cancel order\n"
                      << "12 Add product  13 Delete product  14 Change price  0 Back\n";
            try {
                const int choice = readInt("Select: ");
                switch (choice) {
                case 1: registerCustomer(); break;
                case 2: login(); break;
                case 3: logout(); break;
                case 4: listProducts(); break;
                case 5: searchProducts(); break;
                case 6: addToCart(); break;
                case 7: showCart(); break;
                case 8: removeFromCart(); break;
                case 9: checkout(); break;
                case 10: orderHistory(); break;
                case 11: cancelOrder(); break;
                case 12: addProduct(); break;
                case 13: deleteProduct(); break;
                case 14: changePrice(); break;
                case 0: running = false; break;
                default: std::cout << "Choose a listed menu option.\n";
                }
            } catch (const std::exception& error) {
                std::cout << "Error: " << error.what() << '\n';
            }
        }
    }
};

} // namespace shop

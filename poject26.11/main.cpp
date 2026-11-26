#include "practice.hpp"
#include "shop.hpp"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    bool running = true;
    while (running) {
        std::cout << "\n=== OOP FINAL PRACTICE ===\n"
                  << "1. Exercises 1-21 (demonstration)\n"
                  << "2. Internet store final project\n"
                  << "0. Exit\n"
                  << "Select: ";
        std::string input;
        if (!std::getline(std::cin, input)) break;
        try {
            std::size_t used = 0;
            const int choice = std::stoi(input, &used);
            if (used != input.size()) throw std::invalid_argument("Enter a menu number.");
            switch (choice) {
            case 1:
                practice::runAll();
                break;
            case 2: {
                shop::Store store;
                std::cout << "\nDemo accounts:\n"
                          << "Admin:    admin@shop.local / admin123\n"
                          << "Seller:   seller@shop.local / seller123\n"
                          << "Customer: customer@shop.local / customer123\n";
                store.run();
                break;
            }
            case 0:
                running = false;
                break;
            default:
                std::cout << "Choose 0, 1, or 2.\n";
            }
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }
    std::cout << "Goodbye!\n";
    return 0;
}

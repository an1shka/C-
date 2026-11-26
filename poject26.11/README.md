# OOP Final Practice

The project is a C++17 console application for the OOP practice document.

## Build

From this directory:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o oop_final_practice.exe
.\oop_final_practice.exe
```

Or generate a build with CMake:

```powershell
cmake -S . -B build
cmake --build build
```

## Menu

- **1** runs demonstrations covering exercises 1-21: classes, encapsulation,
  inheritance, polymorphism, abstract classes, interfaces, and combined OOP
  systems.
- **2** opens the interactive online-store project. The store supports customer
  registration and login, catalog search, a shopping cart, checkout, payments,
  delivery selection, receipts, order history/cancellation, and product
  management for admin/seller accounts.

Demo accounts for the store:

| Role | Email | Password |
| --- | --- | --- |
| Administrator | `admin@shop.local` | `admin123` |
| Seller | `seller@shop.local` | `seller123` |
| Customer | `customer@shop.local` | `customer123` |

Store data is kept in memory and resets when the application exits.

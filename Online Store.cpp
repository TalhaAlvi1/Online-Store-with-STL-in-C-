#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>

class Product {
private:
    std::string name;
    double price;
    int stockQuantity;

public:
    Product(const std::string& n, double p, int qty) 
        : name(n), price(p), stockQuantity(qty) {}

    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stockQuantity; }
    void decreaseStock(int qty) { stockQuantity -= qty; }
};

class ShoppingCart {
private:
    std::map<std::string, int> items; // product name -> quantity

public:
    void addItem(const std::string& productName, int quantity) {
        items[productName] += quantity;
    }

    void removeItem(const std::string& productName) {
        items.erase(productName);
    }

    const std::map<std::string, int>& getItems() const {
        return items;
    }

    void clear() {
        items.clear();
    }
};

class OnlineStore {
private:
    std::vector<Product> products;
    ShoppingCart cart;

public:
    void addProduct(const std::string& name, double price, int quantity) {
        products.emplace_back(name, price, quantity);
    }

    void displayProducts() const {
        std::cout << "\nAvailable Products:\n";
        std::cout << std::setw(20) << "Name" << std::setw(10) << "Price" 
                  << std::setw(10) << "Stock" << std::endl;
        std::cout << std::string(40, '-') << std::endl;

        for (const auto& product : products) {
            std::cout << std::setw(20) << product.getName() 
                      << std::setw(10) << "$" << product.getPrice()
                      << std::setw(10) << product.getStock() << std::endl;
        }
    }

    void addToCart(const std::string& productName, int quantity) {
        for (auto& product : products) {
            if (product.getName() == productName) {
                if (product.getStock() >= quantity) {
                    cart.addItem(productName, quantity);
                    std::cout << "Added to cart: " << quantity << "x " << productName << std::endl;
                    return;
                } else {
                    std::cout << "Insufficient stock!" << std::endl;
                    return;
                }
            }
        }
        std::cout << "Product not found!" << std::endl;
    }

    void viewCart() const {
        double total = 0;
        std::cout << "\nShopping Cart:\n";
        std::cout << std::string(40, '-') << std::endl;

        for (const auto& item : cart.getItems()) {
            for (const auto& product : products) {
                if (product.getName() == item.first) {
                    double itemTotal = product.getPrice() * item.second;
                    total += itemTotal;
                    std::cout << std::setw(20) << item.first 
                              << std::setw(10) << item.second 
                              << std::setw(10) << "$" << itemTotal << std::endl;
                }
            }
        }
        std::cout << std::string(40, '-') << std::endl;
        std::cout << "Total: $" << total << std::endl;
    }

    void checkout() {
        for (const auto& item : cart.getItems()) {
            for (auto& product : products) {
                if (product.getName() == item.first) {
                    product.decreaseStock(item.second);
                }
            }
        }
        cart.clear();
        std::cout << "Checkout completed! Thank you for your purchase." << std::endl;
    }
};

int main() {
    OnlineStore store;

    // Add some sample products
    store.addProduct("Laptop", 999.99, 5);
    store.addProduct("Smartphone", 499.99, 10);
    store.addProduct("Headphones", 79.99, 15);
    store.addProduct("Mouse", 29.99, 20);

    while (true) {
        std::cout << "\n=== Online Store Menu ===\n";
        std::cout << "1. Display Products\n";
        std::cout << "2. Add to Cart\n";
        std::cout << "3. View Cart\n";
        std::cout << "4. Checkout\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            store.displayProducts();
        }
        else if (choice == 2) {
            std::string productName;
            int quantity;
            std::cout << "Enter product name: ";
            std::cin.ignore();
            std::getline(std::cin, productName);
            std::cout << "Enter quantity: ";
            std::cin >> quantity;
            store.addToCart(productName, quantity);
        }
        else if (choice == 3) {
            store.viewCart();
        }
        else if (choice == 4) {
            store.checkout();
        }
        else if (choice == 5) {
            std::cout << "Thank you for shopping with us!\n";
            break;
        }
        else {
            std::cout << "Invalid option!\n";
        }
    }

    return 0;
}

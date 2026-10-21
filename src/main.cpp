#include "cart.h"
#include "product_factory.h"

#include <exception>
#include <iostream>
#include <string>

int main() {
    Cart emptyCart;
    emptyCart.printReceipt();
    std::cout << '\n';

    Cart cart;
    const auto addSafely = [&cart](const std::string& type,
                                   const ProductSpec& spec, int quantity) {
        try {
            cart.addItem(ProductFactory::createProduct(type, spec), quantity);
        } catch (const std::exception& error) {
            std::cout << "Не удалось добавить товар: " << error.what() << '\n';
        }
    };

    addSafely("bread", BreadSpec("Ржаной хлеб", 120.0, "ржаное", 750.0), 2);
    addSafely("pastry", PastrySpec("Слойка", 90.0, "вишня", 150.0, 15.0), 3);
    addSafely("cake", CakeSpec("Праздничный торт", 600.0, 3,
                               "ягоды", 120.0, 80.0), 1);

    addSafely("bread", BreadSpec("Хлеб без веса", 120.0, "пшеничное", 0.0), 1);
    addSafely("pastry", PastrySpec("Круассан", 80.0, "шоколад", 100.0, 10.0), 0);
    std::cout << '\n';

    cart.printReceipt();
    return 0;
}

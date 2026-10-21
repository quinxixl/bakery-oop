#include "bread.h"
#include "cake.h"
#include "cart.h"
#include "pastry.h"
#include "product_factory.h"

#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void requireNear(double actual, double expected, const std::string& message) {
    require(std::abs(actual - expected) < 0.001, message);
}

void requireInvalidArgument(const std::function<void()>& operation,
                            const std::string& message) {
    try {
        operation();
    } catch (const std::invalid_argument&) {
        return;
    }
    throw std::runtime_error(message);
}

class CoutCapture final {
public:
    CoutCapture() : original_(std::cout.rdbuf(buffer_.rdbuf())) {}
    ~CoutCapture() { std::cout.rdbuf(original_); }

    std::string str() const { return buffer_.str(); }

private:
    std::ostringstream buffer_;
    std::streambuf* original_;
};

void testProductsAndValidation() {
    Bread bread("Хлеб", 120.0, "ржаное", 750.0);
    Pastry pastry("Слойка", 90.0, "вишня", 150.0, 15.0);
    Cake cake("Торт", 600.0, 3, "ягоды", 120.0, 80.0);

    requireNear(bread.getPrice(), 180.0, "Неверная цена хлеба");
    requireNear(pastry.getPrice(), 150.0, "Неверная цена выпечки");
    requireNear(cake.getPrice(), 920.0, "Неверная цена торта");

    bread.setWeightGrams(500.0);
    requireNear(bread.getPrice(), 120.0, "Цена хлеба не обновилась после смены веса");
    requireInvalidArgument([&bread] { bread.setWeightGrams(0.0); },
                           "Нулевой вес должен отклоняться");
    requireNear(bread.getPrice(), 120.0, "Ошибка изменила прежний вес хлеба");
    requireInvalidArgument([&cake] { cake.setLayers(0); },
                           "Нулевое число слоёв должно отклоняться");
    requireInvalidArgument([&pastry] { pastry.setFillingSurcharge(-1.0); },
                           "Отрицательная доплата должна отклоняться");
    requireInvalidArgument([] { Bread invalid("Хлеб", -1.0, "ржаное", 500.0); },
                           "Отрицательная цена должна отклоняться");
}

void testFactoryAndCart() {
    const BreadSpec breadSpec("Хлеб", 120.0, "ржаное", 750.0);
    requireInvalidArgument([&breadSpec] {
        ProductFactory::createProduct("unknown", breadSpec);
    }, "Неизвестный тип должен отклоняться");
    requireInvalidArgument([&breadSpec] {
        ProductFactory::createProduct("cake", breadSpec);
    }, "Несовпадение типа и параметров должно отклоняться");

    OrderItem item(ProductFactory::createProduct("bread", breadSpec), 2);
    requireNear(item.getLineTotal(), 360.0, "Неверная стоимость позиции");
    item.setQuantity(3);
    requireNear(item.getLineTotal(), 540.0, "Стоимость позиции не пересчиталась");
    requireInvalidArgument([&item] { item.setQuantity(0); },
                           "Нулевое количество должно отклоняться");
    requireNear(item.getLineTotal(), 540.0, "Ошибка изменила стоимость позиции");

    Cart cart;
    requireInvalidArgument([&cart] { cart.addItem(nullptr, 1); },
                           "Пустой товар должен отклоняться");
    requireInvalidArgument([&cart, &breadSpec] {
        cart.addItem(ProductFactory::createProduct("bread", breadSpec), -2);
    }, "Отрицательное количество должно отклоняться");
    requireNear(cart.getTotalPrice(), 0.0, "Ошибки добавили товары в корзину");

    cart.addItem(ProductFactory::createProduct("bread", breadSpec), 2);
    cart.addItem(ProductFactory::createProduct(
        "pastry", PastrySpec("Слойка", 90.0, "вишня", 150.0, 15.0)), 3);
    cart.addItem(ProductFactory::createProduct(
        "cake", CakeSpec("Торт", 600.0, 3, "ягоды", 120.0, 80.0)), 1);
    requireNear(cart.getTotalPrice(), 1730.0, "Неверная сумма корзины");

    {
        CoutCapture capture;
        cart.printReceipt();
        const std::string receipt = capture.str();
        require(receipt.find("тип теста: ржаное") != std::string::npos,
                "В чеке нет деталей хлеба");
        require(receipt.find("начинка: вишня") != std::string::npos,
                "В чеке нет деталей выпечки");
        require(receipt.find("слоёв: 3, декор: ягоды") != std::string::npos,
                "В чеке нет деталей торта");
        require(receipt.find("Итого: 1730.00 руб.") != std::string::npos,
                "В чеке неверная итоговая сумма");
    }

    cart.removeItem(1);
    requireNear(cart.getTotalPrice(), 1280.0, "Удаление не обновило сумму");
    cart.removeItem(1);
    cart.removeItem(0);
    {
        CoutCapture capture;
        cart.printReceipt();
        require(capture.str() == "Корзина пуста.\n", "Неверный вывод пустой корзины");
    }
}

} // namespace

int main() {
    try {
        testProductsAndValidation();
        testFactoryAndCart();
        std::cout << "Все проверки пройдены.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Ошибка проверки: " << error.what() << '\n';
        return 1;
    }
}

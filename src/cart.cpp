#include "cart.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>

OrderItem::OrderItem(std::unique_ptr<Product> product, int quantity)
    : product_(std::move(product)) {
    if (!product_) {
        throw std::invalid_argument("Нельзя добавить пустой указатель на товар");
    }
    setQuantity(quantity);
}

const Product& OrderItem::getProduct() const {
    return *product_;
}

int OrderItem::getQuantity() const {
    return quantity_;
}

double OrderItem::getLineTotal() const {
    return lineTotal_;
}

void OrderItem::setQuantity(int quantity) {
    if (quantity <= 0) {
        throw std::invalid_argument("Количество товара должно быть больше нуля");
    }
    const double total = product_->getPrice() * quantity;
    if (!std::isfinite(total)) {
        throw std::invalid_argument("Стоимость строки заказа слишком велика");
    }
    quantity_ = quantity;
    lineTotal_ = total;
}

void Cart::addItem(std::unique_ptr<Product> product, int quantity) {
    items_.emplace_back(std::move(product), quantity);
}

void Cart::removeItem(std::size_t index) {
    if (index >= items_.size()) {
        throw std::out_of_range("Товара с таким индексом нет в корзине");
    }
    items_.erase(items_.begin() + static_cast<std::ptrdiff_t>(index));
}

double Cart::getTotalPrice() const {
    double total = 0.0;
    for (const OrderItem& item : items_) {
        total += item.getLineTotal();
    }
    return total;
}

void Cart::printReceipt() const {
    if (items_.empty()) {
        std::cout << "Корзина пуста.\n";
        return;
    }

    const auto originalFlags = std::cout.flags();
    const auto originalPrecision = std::cout.precision();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Чек пекарни:\n";
    for (const OrderItem& item : items_) {
        std::cout << "- " << item.getProduct().getName() << " (";
        item.getProduct().printDetails();
        std::cout << ") x " << item.getQuantity()
                  << " = " << item.getLineTotal() << " руб.\n";
    }
    std::cout << "Итого: " << getTotalPrice() << " руб.\n";
    std::cout.flags(originalFlags);
    std::cout.precision(originalPrecision);
}

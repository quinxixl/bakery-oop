#pragma once

#include "product.h"

#include <cstddef>
#include <memory>
#include <vector>

class OrderItem final {
public:
    OrderItem(std::unique_ptr<Product> product, int quantity);

    const Product& getProduct() const;
    int getQuantity() const;
    double getLineTotal() const;
    void setQuantity(int quantity);

private:
    std::unique_ptr<Product> product_;
    int quantity_ = 0;
    double lineTotal_ = 0.0;
};

class Cart final {
public:
    void addItem(std::unique_ptr<Product> product, int quantity);
    void removeItem(std::size_t index);
    double getTotalPrice() const;
    void printReceipt() const;

private:
    std::vector<OrderItem> items_;
};

#pragma once

#include <string>

class Product {
public:
    virtual ~Product() = default;

    virtual double getPrice() const = 0;
    virtual std::string getName() const;
    virtual void printDetails() const = 0;

    double getBasePrice() const;
    void setName(const std::string& name);
    void setBasePrice(double basePrice);

protected:
    Product(const std::string& name, double basePrice);

private:
    std::string name_;
    double basePrice_ = 0.0;
};

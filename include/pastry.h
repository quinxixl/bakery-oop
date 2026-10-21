#pragma once

#include "product.h"

#include <string>

class Pastry final : public Product {
public:
    Pastry(const std::string& name, double pricePer100Grams,
           const std::string& filling, double weightGrams,
           double fillingSurcharge);

    double getPrice() const override;
    void printDetails() const override;

    std::string getFilling() const;
    double getWeightGrams() const;
    double getFillingSurcharge() const;
    void setFilling(const std::string& filling);
    void setWeightGrams(double weightGrams);
    void setFillingSurcharge(double fillingSurcharge);

private:
    std::string filling_;
    double weightGrams_ = 0.0;
    double fillingSurcharge_ = 0.0;
};

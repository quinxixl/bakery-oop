#pragma once

#include "product.h"

#include <string>

class Bread final : public Product {
public:
    Bread(const std::string& name, double pricePer500Grams,
          const std::string& doughType, double weightGrams);

    double getPrice() const override;
    void printDetails() const override;

    std::string getDoughType() const;
    double getWeightGrams() const;
    void setDoughType(const std::string& doughType);
    void setWeightGrams(double weightGrams);

private:
    std::string doughType_;
    double weightGrams_ = 0.0;
};

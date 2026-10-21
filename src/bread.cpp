#include "bread.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

Bread::Bread(const std::string& name, double pricePer500Grams,
             const std::string& doughType, double weightGrams)
    : Product(name, pricePer500Grams) {
    setDoughType(doughType);
    setWeightGrams(weightGrams);
}

double Bread::getPrice() const {
    return getBasePrice() * weightGrams_ / 500.0;
}

void Bread::printDetails() const {
    std::cout << "тип теста: " << doughType_ << ", вес: " << weightGrams_ << " г";
}

std::string Bread::getDoughType() const {
    return doughType_;
}

double Bread::getWeightGrams() const {
    return weightGrams_;
}

void Bread::setDoughType(const std::string& doughType) {
    if (doughType.empty()) {
        throw std::invalid_argument("Тип теста не может быть пустым");
    }
    doughType_ = doughType;
}

void Bread::setWeightGrams(double weightGrams) {
    if (!std::isfinite(weightGrams) || weightGrams <= 0.0) {
        throw std::invalid_argument("Вес хлеба должен быть конечным и больше нуля");
    }
    weightGrams_ = weightGrams;
}

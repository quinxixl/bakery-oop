#include "pastry.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

Pastry::Pastry(const std::string& name, double pricePer100Grams,
               const std::string& filling, double weightGrams,
               double fillingSurcharge)
    : Product(name, pricePer100Grams) {
    setFilling(filling);
    setWeightGrams(weightGrams);
    setFillingSurcharge(fillingSurcharge);
}

double Pastry::getPrice() const {
    return getBasePrice() * weightGrams_ / 100.0 + fillingSurcharge_;
}

void Pastry::printDetails() const {
    std::cout << "начинка: " << filling_ << ", вес: " << weightGrams_ << " г";
}

std::string Pastry::getFilling() const {
    return filling_;
}

double Pastry::getWeightGrams() const {
    return weightGrams_;
}

double Pastry::getFillingSurcharge() const {
    return fillingSurcharge_;
}

void Pastry::setFilling(const std::string& filling) {
    if (filling.empty()) {
        throw std::invalid_argument("Начинка не может быть пустой");
    }
    filling_ = filling;
}

void Pastry::setWeightGrams(double weightGrams) {
    if (!std::isfinite(weightGrams) || weightGrams <= 0.0) {
        throw std::invalid_argument("Вес выпечки должен быть конечным и больше нуля");
    }
    weightGrams_ = weightGrams;
}

void Pastry::setFillingSurcharge(double fillingSurcharge) {
    if (!std::isfinite(fillingSurcharge) || fillingSurcharge < 0.0) {
        throw std::invalid_argument("Доплата за начинку должна быть конечной и неотрицательной");
    }
    fillingSurcharge_ = fillingSurcharge;
}

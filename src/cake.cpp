#include "cake.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

Cake::Cake(const std::string& name, double basePrice, int layers,
           const std::string& decoration, double extraLayerPrice,
           double decorationSurcharge)
    : Product(name, basePrice) {
    setLayers(layers);
    setDecoration(decoration);
    setExtraLayerPrice(extraLayerPrice);
    setDecorationSurcharge(decorationSurcharge);
}

double Cake::getPrice() const {
    return getBasePrice() + (layers_ - 1) * extraLayerPrice_ + decorationSurcharge_;
}

void Cake::printDetails() const {
    std::cout << "слоёв: " << layers_ << ", декор: " << decoration_;
}

int Cake::getLayers() const {
    return layers_;
}

std::string Cake::getDecoration() const {
    return decoration_;
}

double Cake::getExtraLayerPrice() const {
    return extraLayerPrice_;
}

double Cake::getDecorationSurcharge() const {
    return decorationSurcharge_;
}

void Cake::setLayers(int layers) {
    if (layers <= 0) {
        throw std::invalid_argument("Количество слоёв должно быть больше нуля");
    }
    layers_ = layers;
}

void Cake::setDecoration(const std::string& decoration) {
    if (decoration.empty()) {
        throw std::invalid_argument("Описание декора не может быть пустым");
    }
    decoration_ = decoration;
}

void Cake::setExtraLayerPrice(double extraLayerPrice) {
    if (!std::isfinite(extraLayerPrice) || extraLayerPrice < 0.0) {
        throw std::invalid_argument("Цена дополнительного слоя должна быть конечной и неотрицательной");
    }
    extraLayerPrice_ = extraLayerPrice;
}

void Cake::setDecorationSurcharge(double decorationSurcharge) {
    if (!std::isfinite(decorationSurcharge) || decorationSurcharge < 0.0) {
        throw std::invalid_argument("Доплата за декор должна быть конечной и неотрицательной");
    }
    decorationSurcharge_ = decorationSurcharge;
}

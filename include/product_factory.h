#pragma once

#include "product.h"

#include <memory>
#include <string>
#include <variant>

class BreadSpec final {
public:
    BreadSpec(std::string name, double pricePer500Grams,
              std::string doughType, double weightGrams);

    std::string getName() const;
    double getPricePer500Grams() const;
    std::string getDoughType() const;
    double getWeightGrams() const;

private:
    std::string name_;
    double pricePer500Grams_;
    std::string doughType_;
    double weightGrams_;
};

class PastrySpec final {
public:
    PastrySpec(std::string name, double pricePer100Grams,
               std::string filling, double weightGrams,
               double fillingSurcharge);

    std::string getName() const;
    double getPricePer100Grams() const;
    std::string getFilling() const;
    double getWeightGrams() const;
    double getFillingSurcharge() const;

private:
    std::string name_;
    double pricePer100Grams_;
    std::string filling_;
    double weightGrams_;
    double fillingSurcharge_;
};

class CakeSpec final {
public:
    CakeSpec(std::string name, double basePrice, int layers,
             std::string decoration, double extraLayerPrice,
             double decorationSurcharge);

    std::string getName() const;
    double getBasePrice() const;
    int getLayers() const;
    std::string getDecoration() const;
    double getExtraLayerPrice() const;
    double getDecorationSurcharge() const;

private:
    std::string name_;
    double basePrice_;
    int layers_;
    std::string decoration_;
    double extraLayerPrice_;
    double decorationSurcharge_;
};

using ProductSpec = std::variant<BreadSpec, PastrySpec, CakeSpec>;

class ProductFactory final {
public:
    // Тип и вид параметров должны совпадать; проверки значений выполняет товар.
    static std::unique_ptr<Product> createProduct(const std::string& type,
                                                   const ProductSpec& spec);
};

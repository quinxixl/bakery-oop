#pragma once

#include "product.h"

#include <string>

class Cake final : public Product {
public:
    Cake(const std::string& name, double basePrice, int layers,
         const std::string& decoration, double extraLayerPrice,
         double decorationSurcharge);

    double getPrice() const override;
    void printDetails() const override;

    int getLayers() const;
    std::string getDecoration() const;
    double getExtraLayerPrice() const;
    double getDecorationSurcharge() const;
    void setLayers(int layers);
    void setDecoration(const std::string& decoration);
    void setExtraLayerPrice(double extraLayerPrice);
    void setDecorationSurcharge(double decorationSurcharge);

private:
    int layers_ = 0;
    std::string decoration_;
    double extraLayerPrice_ = 0.0;
    double decorationSurcharge_ = 0.0;
};

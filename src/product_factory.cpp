#include "product_factory.h"

#include "bread.h"
#include "cake.h"
#include "pastry.h"

#include <stdexcept>
#include <utility>

BreadSpec::BreadSpec(std::string name, double pricePer500Grams,
                     std::string doughType, double weightGrams)
    : name_(std::move(name)), pricePer500Grams_(pricePer500Grams),
      doughType_(std::move(doughType)), weightGrams_(weightGrams) {}

std::string BreadSpec::getName() const { return name_; }
double BreadSpec::getPricePer500Grams() const { return pricePer500Grams_; }
std::string BreadSpec::getDoughType() const { return doughType_; }
double BreadSpec::getWeightGrams() const { return weightGrams_; }

PastrySpec::PastrySpec(std::string name, double pricePer100Grams,
                       std::string filling, double weightGrams,
                       double fillingSurcharge)
    : name_(std::move(name)), pricePer100Grams_(pricePer100Grams),
      filling_(std::move(filling)), weightGrams_(weightGrams),
      fillingSurcharge_(fillingSurcharge) {}

std::string PastrySpec::getName() const { return name_; }
double PastrySpec::getPricePer100Grams() const { return pricePer100Grams_; }
std::string PastrySpec::getFilling() const { return filling_; }
double PastrySpec::getWeightGrams() const { return weightGrams_; }
double PastrySpec::getFillingSurcharge() const { return fillingSurcharge_; }

CakeSpec::CakeSpec(std::string name, double basePrice, int layers,
                   std::string decoration, double extraLayerPrice,
                   double decorationSurcharge)
    : name_(std::move(name)), basePrice_(basePrice), layers_(layers),
      decoration_(std::move(decoration)), extraLayerPrice_(extraLayerPrice),
      decorationSurcharge_(decorationSurcharge) {}

std::string CakeSpec::getName() const { return name_; }
double CakeSpec::getBasePrice() const { return basePrice_; }
int CakeSpec::getLayers() const { return layers_; }
std::string CakeSpec::getDecoration() const { return decoration_; }
double CakeSpec::getExtraLayerPrice() const { return extraLayerPrice_; }
double CakeSpec::getDecorationSurcharge() const { return decorationSurcharge_; }

std::unique_ptr<Product> ProductFactory::createProduct(const std::string& type,
                                                        const ProductSpec& spec) {
    if (type == "bread") {
        const auto* bread = std::get_if<BreadSpec>(&spec);
        if (!bread) {
            throw std::invalid_argument("Для bread нужны параметры BreadSpec");
        }
        return std::make_unique<Bread>(bread->getName(), bread->getPricePer500Grams(),
                                       bread->getDoughType(), bread->getWeightGrams());
    }
    if (type == "pastry") {
        const auto* pastry = std::get_if<PastrySpec>(&spec);
        if (!pastry) {
            throw std::invalid_argument("Для pastry нужны параметры PastrySpec");
        }
        return std::make_unique<Pastry>(pastry->getName(), pastry->getPricePer100Grams(),
                                        pastry->getFilling(), pastry->getWeightGrams(),
                                        pastry->getFillingSurcharge());
    }
    if (type == "cake") {
        const auto* cake = std::get_if<CakeSpec>(&spec);
        if (!cake) {
            throw std::invalid_argument("Для cake нужны параметры CakeSpec");
        }
        return std::make_unique<Cake>(cake->getName(), cake->getBasePrice(),
                                      cake->getLayers(), cake->getDecoration(),
                                      cake->getExtraLayerPrice(),
                                      cake->getDecorationSurcharge());
    }
    throw std::invalid_argument("Неизвестный тип товара: " + type);
}

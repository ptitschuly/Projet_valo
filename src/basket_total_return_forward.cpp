#include "basket_total_return_forward.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>

BasketTotalReturnForward::BasketTotalReturnForward(const std::string& name,
                                                 const std::vector<BasketAsset>& basket,
                                                 double notional,
                                                 double maturity,
                                                 double forwardRate,
                                                 double riskFreeRate)
    : Instrument(name),
      basket_(basket),
      notional_(notional),
      maturity_(maturity),
      forwardRate_(forwardRate),
      riskFreeRate_(riskFreeRate) {

    // Normalisation des poids pour qu'ils somment à 1
    double totalWeight = 0.0;
    for (const auto& asset : basket_) {
        totalWeight += asset.weight;
    }

    if (totalWeight > 0.0) {
        for (auto& asset : basket_) {
            asset.weight /= totalWeight;
        }
    }
}

double BasketTotalReturnForward::getPrice() const {
    // Prix du forward = valeur actualisée du paiement attendu
    double expectedBasketReturn = calculateBasketReturn(maturity_);
    double expectedPayment = notional_ * (expectedBasketReturn - forwardRate_);
    double discountFactor = calculateDiscountFactor(maturity_);

    return expectedPayment * discountFactor;
}

double BasketTotalReturnForward::getBasketTotalReturn() const {
    return calculateBasketReturn(maturity_);
}

double BasketTotalReturnForward::getForwardRate() const {
    return forwardRate_;
}

double BasketTotalReturnForward::getNotional() const {
    return notional_;
}

double BasketTotalReturnForward::getMaturity() const {
    return maturity_;
}

double BasketTotalReturnForward::getBasketValue() const {
    double value = 0.0;
    for (const auto& asset : basket_) {
        value += asset.spotPrice * asset.weight;
    }
    return value;
}

std::vector<double> BasketTotalReturnForward::getAssetWeights() const {
    std::vector<double> weights;
    for (const auto& asset : basket_) {
        weights.push_back(asset.weight);
    }
    return weights;
}

double BasketTotalReturnForward::calculateBasketReturn(double time) const {
    double basketReturn = 0.0;

    for (const auto& asset : basket_) {
        double assetReturn = calculateAssetReturn(asset, time);
        basketReturn += assetReturn * asset.weight;
    }

    return basketReturn;
}

double BasketTotalReturnForward::calculateAssetReturn(const BasketAsset& asset, double time) const {
    // Rendement total = appréciation + dividendes
    // Approximation : appréciation = (r - q) * t + volatilité ajustée
    double expectedAppreciation = (riskFreeRate_ - asset.dividendYield) * time;

    // Ajustement pour la volatilité (effet de convexité)
    double volatilityAdjustment = 0.5 * asset.volatility * asset.volatility * time;

    double totalReturn = expectedAppreciation + asset.dividendYield * time + volatilityAdjustment;

    return totalReturn;
}

double BasketTotalReturnForward::calculateDiscountFactor(double time) const {
    return std::exp(-riskFreeRate_ * time);
}
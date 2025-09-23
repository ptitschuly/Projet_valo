#pragma once

#include "instrument.h"
#include <vector>
#include <string>

struct BasketAsset {
    double spotPrice;      // Prix actuel de l'actif
    double weight;         // Poids dans le panier
    double dividendYield;  // Rendement des dividendes
    double volatility;     // Volatilité de l'actif
    std::string name;      // Nom de l'actif
};

class BasketTotalReturnForward : public Instrument {
public:
    BasketTotalReturnForward(const std::string& name,
                           const std::vector<BasketAsset>& basket,
                           double notional,
                           double maturity,
                           double forwardRate,
                           double riskFreeRate);

    double getPrice() const override;

    // Méthodes supplémentaires pour l'analyse
    double getBasketTotalReturn() const;
    double getForwardRate() const;
    double getNotional() const;
    double getMaturity() const;

    // Analyse du panier
    double getBasketValue() const;
    std::vector<double> getAssetWeights() const;

private:
    std::vector<BasketAsset> basket_;
    double notional_;
    double maturity_;
    double forwardRate_;
    double riskFreeRate_;

    // Méthodes privées pour les calculs
    double calculateBasketReturn(double time) const;
    double calculateDiscountFactor(double time) const;
    double calculateAssetReturn(const BasketAsset& asset, double time) const;
};
#pragma once

#include "instrument.h"
#include <vector>
#include <string>

struct UnderlyingTRSAsset {
    double spotPrice;      // Prix actuel de l'actif
    double dividendYield;  // Rendement des dividendes
    double volatility;     // Volatilité de l'actif
    std::string name;      // Nom de l'actif
};

class TotalReturnSwap : public Instrument {
public:
    TotalReturnSwap(const std::string& name,
                   const UnderlyingTRSAsset& underlying,
                   double notional,
                   double maturity,
                   double swapRate,
                   double riskFreeRate,
                   double paymentFrequency = 0.25); // Trimestriel par défaut

    double getPrice() const override;

    // Méthodes supplémentaires pour l'analyse
    double getExpectedTotalReturn() const;
    double getSwapRate() const;
    double getNotional() const;
    double getMaturity() const;

    // Calcul des flux de trésorerie
    std::vector<double> getCashFlows() const;

private:
    UnderlyingTRSAsset underlying_;
    double notional_;
    double maturity_;
    double swapRate_;
    double riskFreeRate_;
    double paymentFrequency_;

    // Méthodes privées pour les calculs
    double calculateAssetReturn(double time) const;
    double calculateDiscountFactor(double time) const;
};
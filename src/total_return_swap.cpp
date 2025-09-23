#include "total_return_swap.h"
#include <cmath>
#include <algorithm>
#include <iostream>

TotalReturnSwap::TotalReturnSwap(const std::string& name,
                               const UnderlyingTRSAsset& underlying,
                               double notional,
                               double maturity,
                               double swapRate,
                               double riskFreeRate,
                               double paymentFrequency)
    : Instrument(name),
      underlying_(underlying),
      notional_(notional),
      maturity_(maturity),
      swapRate_(swapRate),
      riskFreeRate_(riskFreeRate),
      paymentFrequency_(paymentFrequency) {
}

double TotalReturnSwap::getPrice() const {
    std::vector<double> cashFlows = getCashFlows();
    double price = 0.0;

    // Actualisation des flux de trésorerie
    for (size_t i = 0; i < cashFlows.size(); ++i) {
        double time = (i + 1) * paymentFrequency_;
        double discountFactor = calculateDiscountFactor(time);
        price += cashFlows[i] * discountFactor;
    }

    return price;
}

double TotalReturnSwap::getExpectedTotalReturn() const {
    // Rendement total attendu = rendement des dividendes + appréciation attendue
    // L'appréciation attendue est approximée par (r - q) * T où r est le taux sans risque
    double expectedAppreciation = (riskFreeRate_ - underlying_.dividendYield) * maturity_;
    double expectedDividendReturn = underlying_.dividendYield * maturity_;

    return expectedAppreciation + expectedDividendReturn;
}

double TotalReturnSwap::getSwapRate() const {
    return swapRate_;
}

double TotalReturnSwap::getNotional() const {
    return notional_;
}

double TotalReturnSwap::getMaturity() const {
    return maturity_;
}

std::vector<double> TotalReturnSwap::getCashFlows() const {
    std::vector<double> cashFlows;

    int numPayments = static_cast<int>(std::ceil(maturity_ / paymentFrequency_));
    double periodicSwapPayment = notional_ * swapRate_ * paymentFrequency_;

    for (int i = 0; i < numPayments; ++i) {
        double time = (i + 1) * paymentFrequency_;

        // Rendement total de l'actif à cette période
        double assetReturn = calculateAssetReturn(time);
        double totalReturnPayment = notional_ * assetReturn * paymentFrequency_;

        // Flux net : rendement total reçu - paiement du swap
        double netCashFlow = totalReturnPayment - periodicSwapPayment;
        cashFlows.push_back(netCashFlow);
    }

    return cashFlows;
}

double TotalReturnSwap::calculateAssetReturn(double time) const {
    // Approximation simplifiée du rendement total
    // Rendement = appréciation + dividendes
    // L'appréciation suit un processus géométrique brownien

    // Pour une approximation, on utilise le rendement attendu
    double expectedReturn = (riskFreeRate_ - underlying_.dividendYield) +
                           underlying_.dividendYield;

    // Ajustement pour le temps écoulé
    double timeFraction = time / maturity_;
    return expectedReturn * timeFraction;
}

double TotalReturnSwap::calculateDiscountFactor(double time) const {
    return std::exp(-riskFreeRate_ * time);
}
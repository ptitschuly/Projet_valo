#include "collateralized_product.h"
#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>
#include <iostream>

CollateralizedProduct::CollateralizedProduct(const std::string& name,
                                           const std::vector<UnderlyingAsset>& assets,
                                           const std::vector<Tranche>& tranches,
                                           double riskFreeRate,
                                           double timeHorizon)
    : Instrument(name),
      underlyingAssets_(assets),
      tranches_(tranches),
      riskFreeRate_(riskFreeRate),
      timeHorizon_(timeHorizon) {
}

double CollateralizedProduct::getPrice() const {
    double totalValue = 0.0;

    // Calculer la valeur totale des tranches
    for (const auto& tranche : tranches_) {
        totalValue += tranche.price;
    }

    return totalValue;
}

double CollateralizedProduct::calculateExpectedLoss() const {
    double totalNotional = 0.0;
    double expectedLoss = 0.0;

    for (const auto& asset : underlyingAssets_) {
        totalNotional += asset.notional;
        expectedLoss += asset.notional * asset.defaultProbability * (1.0 - asset.recoveryRate);
    }

    return totalNotional > 0.0 ? expectedLoss / totalNotional : 0.0;
}

double CollateralizedProduct::calculateValueAtRisk(double confidenceLevel) const {
    // Simulation simple pour estimer le VaR
    const int numSimulations = 10000;
    std::vector<double> losses;

    for (int i = 0; i < numSimulations; ++i) {
        losses.push_back(simulatePortfolioLoss());
    }

    std::sort(losses.begin(), losses.end());
    int index = static_cast<int>((1.0 - confidenceLevel) * numSimulations);

    return index < losses.size() ? losses[index] : losses.back();
}

std::vector<double> CollateralizedProduct::getTranchePrices() const {
    std::vector<double> prices;
    for (const auto& tranche : tranches_) {
        prices.push_back(tranche.price);
    }
    return prices;
}

void CollateralizedProduct::runMonteCarloSimulation(int numSimulations) {
    double totalNotional = 0.0;
    for (const auto& asset : underlyingAssets_) {
        totalNotional += asset.notional;
    }

    // Calculer la perte attendue
    double expectedLoss = calculateExpectedLoss() * totalNotional;

    // Valoriser chaque tranche
    for (auto& tranche : tranches_) {
        tranche.price = calculateTranchePrice(tranche, expectedLoss);
    }
}

double CollateralizedProduct::simulatePortfolioLoss() const {
    double totalLoss = 0.0;

    for (const auto& asset : underlyingAssets_) {
        // Simulation d'un défaut basé sur la probabilité
        double randomValue = generateNormalRandom(0.0, 1.0);
        bool defaultOccurs = (randomValue < asset.defaultProbability);

        if (defaultOccurs) {
            double loss = asset.notional * (1.0 - asset.recoveryRate);
            totalLoss += loss;
        }
    }

    return totalLoss;
}

double CollateralizedProduct::calculateTrancheLoss(double portfolioLoss, const Tranche& tranche) const {
    double totalNotional = 0.0;
    for (const auto& asset : underlyingAssets_) {
        totalNotional += asset.notional;
    }

    double lossRatio = portfolioLoss / totalNotional;

    if (lossRatio <= tranche.attachmentPoint) {
        return 0.0;  // Pas de perte pour cette tranche
    } else if (lossRatio >= tranche.detachmentPoint) {
        return tranche.notional;  // Perte totale
    } else {
        // Perte partielle
        double trancheThickness = tranche.detachmentPoint - tranche.attachmentPoint;
        double lossInTranche = (lossRatio - tranche.attachmentPoint) / trancheThickness;
        return tranche.notional * lossInTranche;
    }
}

double CollateralizedProduct::calculateTranchePrice(const Tranche& tranche, double expectedLoss) const {
    // Modèle simplifié de valorisation de tranche
    // Prix = Notional * (1 - ExpectedLossRatio) + flux de coupons

    double totalNotional = 0.0;
    for (const auto& asset : underlyingAssets_) {
        totalNotional += asset.notional;
    }

    double expectedLossRatio = expectedLoss / totalNotional;

    // Calculer la perte attendue pour cette tranche
    double trancheExpectedLoss = 0.0;
    if (expectedLossRatio > tranche.attachmentPoint) {
        if (expectedLossRatio >= tranche.detachmentPoint) {
            trancheExpectedLoss = tranche.notional;
        } else {
            double trancheThickness = tranche.detachmentPoint - tranche.attachmentPoint;
            double lossRatio = (expectedLossRatio - tranche.attachmentPoint) / trancheThickness;
            trancheExpectedLoss = tranche.notional * lossRatio;
        }
    }

    // Valorisation simplifiée : prix = notional - perte attendue + valeur présente des coupons
    double couponPV = tranche.notional * tranche.couponRate * timeHorizon_ *
                     std::exp(-riskFreeRate_ * timeHorizon_);

    double trancheValue = tranche.notional - trancheExpectedLoss + couponPV;

    return std::max(0.0, trancheValue);  // Le prix ne peut pas être négatif
}

double CollateralizedProduct::generateNormalRandom(double mean, double stddev) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::normal_distribution<> dist(mean, stddev);
    return dist(gen);
}
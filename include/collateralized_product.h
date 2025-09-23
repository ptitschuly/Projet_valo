#pragma once

#include "instrument.h"
#include <vector>
#include <memory>

struct Tranche {
    std::string name;
    double attachmentPoint;  // Point d'attachement (pourcentage)
    double detachmentPoint;  // Point de détachement (pourcentage)
    double notional;         // Montant notionnel
    double couponRate;       // Taux de coupon
    double price;            // Prix de la tranche

    Tranche(const std::string& n, double attach, double detach, double notional, double coupon)
        : name(n), attachmentPoint(attach), detachmentPoint(detach),
          notional(notional), couponRate(coupon), price(0.0) {}
};

struct UnderlyingAsset {
    double notional;         // Montant notionnel de l'actif
    double recoveryRate;     // Taux de récupération en cas de défaut
    double defaultProbability; // Probabilité de défaut
    double currentValue;     // Valeur actuelle

    UnderlyingAsset(double notional, double recovery, double defProb, double value)
        : notional(notional), recoveryRate(recovery),
          defaultProbability(defProb), currentValue(value) {}
};

class CollateralizedProduct : public Instrument {
public:
    CollateralizedProduct(const std::string& name,
                         const std::vector<UnderlyingAsset>& assets,
                         const std::vector<Tranche>& tranches,
                         double riskFreeRate,
                         double timeHorizon);

    double getPrice() const override;

    // Méthodes pour l'analyse de risque
    double calculateExpectedLoss() const;
    double calculateValueAtRisk(double confidenceLevel) const;
    std::vector<double> getTranchePrices() const;

    // Simulation Monte Carlo pour la valorisation
    void runMonteCarloSimulation(int numSimulations);

private:
    std::vector<UnderlyingAsset> underlyingAssets_;
    std::vector<Tranche> tranches_;
    double riskFreeRate_;
    double timeHorizon_;

    // Méthodes privées pour les calculs
    double simulatePortfolioLoss() const;
    double calculateTrancheLoss(double portfolioLoss, const Tranche& tranche) const;
    double calculateTranchePrice(const Tranche& tranche, double expectedLoss) const;

    // Distribution des pertes selon une loi normale
    double generateNormalRandom(double mean, double stddev) const;
};
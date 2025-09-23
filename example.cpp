#include <iostream>
#include "european_option.h"
#include "american_option.h"
#include "greeks.h"
#include "monte_carlo.h"
#include "collateralized_product.h"
#include "total_return_swap.h"
#include "basket_total_return_forward.h"

int main() {
    // Exemple 1: Valorisation d'une option européenne call
    std::cout << "=== Exemple 1: Option Européenne Call ===" << std::endl;
    EuropeanOption call("European Call", 100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    double callPrice = call.getPrice();
    std::cout << "Prix de l'option call: " << callPrice << std::endl;

    // Calcul des Greeks
    Greeks g = GreeksCalculator::calculateEuropeanCall(100.0, 100.0, 1.0, 0.05, 0.2);
    std::cout << "Delta: " << g.delta << std::endl;
    std::cout << "Gamma: " << g.gamma << std::endl;
    std::cout << "Theta: " << g.theta << std::endl;
    std::cout << "Vega: " << g.vega << std::endl;
    std::cout << "Rho: " << g.rho << std::endl;

    std::cout << "\n=== Exemple 2: Option Américaine Put ===" << std::endl;
    AmericanOption put("American Put", 100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    double putPrice = put.getPrice();
    std::cout << "Prix de l'option put américaine: " << putPrice << std::endl;

    std::cout << "\n=== Exemple 3: Monte Carlo ===" << std::endl;
    double mcPrice = MonteCarlo::priceOption(100.0, 100.0, 1.0, 0.05, 0.2, 100000, true);
    std::cout << "Prix par Monte Carlo (call): " << mcPrice << std::endl;

    std::cout << "\n=== Exemple 4: Produit Collatéralisé (CDO) ===" << std::endl;

    // Créer un portefeuille d'actifs sous-jacents
    std::vector<UnderlyingAsset> assets;
    assets.emplace_back(1000000.0, 0.4, 0.02, 1000000.0);  // Actif 1
    assets.emplace_back(1000000.0, 0.4, 0.03, 1000000.0);  // Actif 2
    assets.emplace_back(1000000.0, 0.4, 0.025, 1000000.0); // Actif 3
    assets.emplace_back(1000000.0, 0.4, 0.015, 1000000.0); // Actif 4
    assets.emplace_back(1000000.0, 0.4, 0.035, 1000000.0); // Actif 5

    // Créer les tranches du CDO
    std::vector<Tranche> tranches;
    tranches.emplace_back("Equity Tranche", 0.0, 0.05, 200000.0, 0.15);     // 0-5%
    tranches.emplace_back("Mezzanine Tranche", 0.05, 0.15, 300000.0, 0.08);  // 5-15%
    tranches.emplace_back("Senior Tranche", 0.15, 0.30, 500000.0, 0.04);     // 15-30%

    // Créer le CDO
    CollateralizedProduct cdo("Sample CDO", assets, tranches, 0.03, 5.0);

    // Calculer la perte attendue
    double expectedLoss = cdo.calculateExpectedLoss();
    std::cout << "Perte attendue du portefeuille: " << expectedLoss * 100 << "%" << std::endl;

    // Calculer le Value at Risk
    double var95 = cdo.calculateValueAtRisk(0.95);
    std::cout << "Value at Risk (95%): " << var95 << std::endl;

    // Exécuter la simulation Monte Carlo
    cdo.runMonteCarloSimulation(10000);

    // Afficher les prix des tranches
    std::vector<double> tranchePrices = cdo.getTranchePrices();
    std::cout << "Prix des tranches:" << std::endl;
    for (size_t i = 0; i < tranches.size(); ++i) {
        std::cout << "  " << tranches[i].name << ": " << tranchePrices[i] << std::endl;
    }

    // Prix total du CDO
    double totalPrice = cdo.getPrice();
    std::cout << "Prix total du CDO: " << totalPrice << std::endl;

    // === Exemple 5: Total Return Swap ===
    std::cout << "\n=== Exemple 5: Total Return Swap ===" << std::endl;

    // Créer un actif sous-jacent pour le TRS
    UnderlyingTRSAsset trsAsset{120.0, 0.025, 0.22, "Tech Stock"};

    // Créer un TRS : nom, actif, notionnel, maturité, taux swap, taux sans risque
    TotalReturnSwap trs("Tech Stock TRS", trsAsset, 5000000.0, 3.0, 0.045, 0.03);

    double trsPrice = trs.getPrice();
    std::cout << "Prix du TRS: " << trsPrice << std::endl;

    double expectedReturn = trs.getExpectedTotalReturn();
    std::cout << "Rendement total attendu: " << expectedReturn * 100 << "%" << std::endl;

    std::vector<double> cashFlows = trs.getCashFlows();
    std::cout << "Nombre de flux de trésorerie: " << cashFlows.size() << std::endl;
    std::cout << "Premier flux: " << cashFlows[0] << std::endl;

    // === Exemple 6: Basket Total Return Forward ===
    std::cout << "\n=== Exemple 6: Basket Total Return Forward ===" << std::endl;

    // Créer un panier d'actifs diversifiés
    std::vector<BasketAsset> basket = {
        {100.0, 0.4, 0.02, 0.25, "Action Tech"},     // 40%
        {200.0, 0.35, 0.035, 0.18, "Action Finance"}, // 35%
        {50.0, 0.25, 0.015, 0.30, "Action Energie"}   // 25%
    };

    // Créer un Basket TRF : nom, panier, notionnel, maturité, taux forward, taux sans risque
    BasketTotalReturnForward basketTrf("Diversified Basket TRF", basket, 10000000.0, 2.0, 0.04, 0.028);

    double basketPrice = basketTrf.getPrice();
    std::cout << "Prix du Basket TRF: " << basketPrice << std::endl;

    double basketReturn = basketTrf.getBasketTotalReturn();
    std::cout << "Rendement total du panier: " << basketReturn * 100 << "%" << std::endl;

    double basketValue = basketTrf.getBasketValue();
    std::cout << "Valeur actuelle du panier: " << basketValue << std::endl;

    std::vector<double> weights = basketTrf.getAssetWeights();
    std::cout << "Poids des actifs dans le panier: ";
    for (size_t i = 0; i < weights.size(); ++i) {
        std::cout << basket[i].name << ": " << weights[i] * 100 << "%";
        if (i < weights.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    return 0;
}
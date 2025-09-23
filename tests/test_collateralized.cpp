#include "collateralized_product.h"
#include <cassert>
#include <iostream>
#include <vector>

void testCollateralizedProduct() {
    // Créer un portefeuille d'actifs sous-jacents
    std::vector<UnderlyingAsset> assets;
    assets.emplace_back(1000000.0, 0.4, 0.02, 1000000.0);  // Actif 1
    assets.emplace_back(1000000.0, 0.4, 0.03, 1000000.0);  // Actif 2
    assets.emplace_back(1000000.0, 0.4, 0.025, 1000000.0); // Actif 3

    // Créer les tranches du CDO
    std::vector<Tranche> tranches;
    tranches.emplace_back("Equity Tranche", 0.0, 0.05, 100000.0, 0.15);    // 0-5%
    tranches.emplace_back("Mezzanine Tranche", 0.05, 0.15, 150000.0, 0.08); // 5-15%
    tranches.emplace_back("Senior Tranche", 0.15, 0.30, 200000.0, 0.04);    // 15-30%

    // Créer le CDO
    CollateralizedProduct cdo("Test CDO", assets, tranches, 0.03, 5.0);

    // Tester la perte attendue
    double expectedLoss = cdo.calculateExpectedLoss();
    std::cout << "Expected Loss: " << expectedLoss << std::endl;
    assert(expectedLoss >= 0.0 && expectedLoss <= 1.0);

    // Tester le Value at Risk
    double var95 = cdo.calculateValueAtRisk(0.95);
    std::cout << "VaR 95%: " << var95 << std::endl;
    assert(var95 >= 0.0);

    // Tester la simulation Monte Carlo
    cdo.runMonteCarloSimulation(1000);

    // Tester les prix des tranches
    std::vector<double> tranchePrices = cdo.getTranchePrices();
    std::cout << "Tranche Prices: ";
    for (double price : tranchePrices) {
        std::cout << price << " ";
        assert(price >= 0.0);
    }
    std::cout << std::endl;

    // Tester le prix total
    double totalPrice = cdo.getPrice();
    std::cout << "Total CDO Price: " << totalPrice << std::endl;
    assert(totalPrice >= 0.0);

    std::cout << "Collateralized Product test passed!" << std::endl;
}

void testTrancheMechanics() {
    // Test des mécaniques de tranchage
    std::vector<UnderlyingAsset> assets;
    assets.emplace_back(1000000.0, 0.4, 0.05, 1000000.0);  // Haute probabilité de défaut

    std::vector<Tranche> tranches;
    tranches.emplace_back("Equity", 0.0, 0.10, 100000.0, 0.20);   // 0-10%
    tranches.emplace_back("Senior", 0.10, 0.50, 200000.0, 0.05);  // 10-50%

    CollateralizedProduct cdo("Tranche Test CDO", assets, tranches, 0.03, 3.0);

    // Avec une probabilité de défaut de 5%, la perte attendue devrait être d'environ 3%
    double expectedLoss = cdo.calculateExpectedLoss();
    std::cout << "Expected Loss (high default prob): " << expectedLoss << std::endl;

    cdo.runMonteCarloSimulation(1000);
    std::vector<double> prices = cdo.getTranchePrices();

    // La tranche equity devrait être plus affectée que la tranche senior
    std::cout << "Equity tranche price: " << prices[0] << std::endl;
    std::cout << "Senior tranche price: " << prices[1] << std::endl;

    // La tranche senior devrait avoir un prix plus élevé
    assert(prices[1] > prices[0]);

    std::cout << "Tranche mechanics test passed!" << std::endl;
}
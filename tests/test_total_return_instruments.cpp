#include "total_return_swap.h"
#include "basket_total_return_forward.h"
#include <cassert>
#include <iostream>
#include <vector>

void testTotalReturnSwap() {
    std::cout << "=== Testing Total Return Swap ===" << std::endl;

    // Créer un actif sous-jacent
    UnderlyingTRSAsset asset{100.0, 0.02, 0.25, "Test Asset"};

    // Créer un TRS
    TotalReturnSwap trs("Test TRS", asset, 1000000.0, 2.0, 0.04, 0.03);

    double price = trs.getPrice();
    std::cout << "TRS Price: " << price << std::endl;
    assert(price != 0.0); // Le prix peut être positif ou négatif selon les paramètres

    double expectedReturn = trs.getExpectedTotalReturn();
    std::cout << "Expected Total Return: " << expectedReturn << std::endl;
    assert(expectedReturn > 0.0);

    double swapRate = trs.getSwapRate();
    std::cout << "Swap Rate: " << swapRate << std::endl;
    assert(swapRate == 0.04);

    double notional = trs.getNotional();
    std::cout << "Notional: " << notional << std::endl;
    assert(notional == 1000000.0);

    std::vector<double> cashFlows = trs.getCashFlows();
    std::cout << "Number of cash flows: " << cashFlows.size() << std::endl;
    assert(cashFlows.size() > 0);

    std::cout << "Total Return Swap tests passed!" << std::endl;
}

void testBasketTotalReturnForward() {
    std::cout << "=== Testing Basket Total Return Forward ===" << std::endl;

    // Créer un panier d'actifs
    std::vector<BasketAsset> basket = {
        {100.0, 0.5, 0.02, 0.25, "Asset A"},  // 50% poids
        {150.0, 0.3, 0.03, 0.20, "Asset B"},  // 30% poids
        {80.0, 0.2, 0.025, 0.30, "Asset C"}   // 20% poids
    };

    // Créer un Basket TRF
    BasketTotalReturnForward basketTrf("Test Basket TRF", basket, 2000000.0, 1.5, 0.035, 0.025);

    double price = basketTrf.getPrice();
    std::cout << "Basket TRF Price: " << price << std::endl;
    assert(price != 0.0);

    double basketReturn = basketTrf.getBasketTotalReturn();
    std::cout << "Basket Total Return: " << basketReturn << std::endl;
    assert(basketReturn > 0.0);

    double forwardRate = basketTrf.getForwardRate();
    std::cout << "Forward Rate: " << forwardRate << std::endl;
    assert(forwardRate == 0.035);

    double basketValue = basketTrf.getBasketValue();
    std::cout << "Basket Value: " << basketValue << std::endl;
    assert(basketValue > 0.0);

    std::vector<double> weights = basketTrf.getAssetWeights();
    std::cout << "Asset Weights: ";
    for (double w : weights) {
        std::cout << w << " ";
    }
    std::cout << std::endl;
    assert(weights.size() == 3);

    // Vérifier que les poids somment à 1 (normalisation)
    double sumWeights = 0.0;
    for (double w : weights) {
        sumWeights += w;
    }
    assert(std::abs(sumWeights - 1.0) < 1e-6);

    std::cout << "Basket Total Return Forward tests passed!" << std::endl;
}

void testBasketTotalReturnForwardEdgeCases() {
    std::cout << "=== Testing Basket TRF Edge Cases ===" << std::endl;

    // Test avec un seul actif
    std::vector<BasketAsset> singleAsset = {
        {100.0, 1.0, 0.02, 0.25, "Single Asset"}
    };

    BasketTotalReturnForward singleTrf("Single Asset TRF", singleAsset, 1000000.0, 1.0, 0.03, 0.025);
    double singlePrice = singleTrf.getPrice();
    std::cout << "Single Asset TRF Price: " << singlePrice << std::endl;
    assert(singlePrice != 0.0);

    // Test avec poids nuls (devrait être normalisé)
    std::vector<BasketAsset> zeroWeights = {
        {100.0, 0.0, 0.02, 0.25, "Asset 1"},
        {100.0, 0.0, 0.02, 0.25, "Asset 2"},
        {100.0, 1.0, 0.02, 0.25, "Asset 3"}
    };

    BasketTotalReturnForward zeroWeightTrf("Zero Weight TRF", zeroWeights, 1000000.0, 1.0, 0.03, 0.025);
    std::vector<double> normalizedWeights = zeroWeightTrf.getAssetWeights();

    // Le dernier actif devrait avoir un poids de 1.0 après normalisation
    assert(std::abs(normalizedWeights.back() - 1.0) < 1e-6);

    std::cout << "Edge case tests passed!" << std::endl;
}
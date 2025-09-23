#include <iostream>

// Déclarations des fonctions de test
void testEuropeanCall();
void testEuropeanPut();
void testAmericanCall();
void testAmericanPut();

void testBlackScholesCall();
void testBlackScholesPut();
void testPutCallParity();

void testBinomialCall();
void testBinomialPut();

void testMonteCarloCall();
void testMonteCarloPut();

void testGreeksCall();
void testGreeksPut();

void testCollateralizedProduct();
void testTrancheMechanics();

void testTotalReturnSwap();
void testBasketTotalReturnForward();
void testBasketTotalReturnForwardEdgeCases();

int main() {
    std::cout << "=== Exécution de tous les tests ===\n" << std::endl;

    try {
        std::cout << "Tests des options..." << std::endl;
        testEuropeanCall();
        testEuropeanPut();
        testAmericanCall();
        testAmericanPut();
        std::cout << "✓ Tests options OK\n" << std::endl;

        std::cout << "Tests Black-Scholes..." << std::endl;
        testBlackScholesCall();
        testBlackScholesPut();
        testPutCallParity();
        std::cout << "✓ Tests Black-Scholes OK\n" << std::endl;

        std::cout << "Tests Binomial..." << std::endl;
        testBinomialCall();
        testBinomialPut();
        std::cout << "✓ Tests Binomial OK\n" << std::endl;

        std::cout << "Tests Monte Carlo..." << std::endl;
        testMonteCarloCall();
        testMonteCarloPut();
        std::cout << "✓ Tests Monte Carlo OK\n" << std::endl;

        std::cout << "Tests Greeks..." << std::endl;
        testGreeksCall();
        testGreeksPut();
        std::cout << "✓ Tests Greeks OK\n" << std::endl;

        std::cout << "Tests Produits Collatéralisés..." << std::endl;
        testCollateralizedProduct();
        testTrancheMechanics();
        std::cout << "✓ Tests Produits Collatéralisés OK\n" << std::endl;

        std::cout << "Tests Total Return Instruments..." << std::endl;
        testTotalReturnSwap();
        testBasketTotalReturnForward();
        testBasketTotalReturnForwardEdgeCases();
        std::cout << "✓ Tests Total Return Instruments OK\n" << std::endl;

        std::cout << "=== Tous les tests sont passés ! ===" << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Erreur lors des tests: " << e.what() << std::endl;
        return 1;
    }
}
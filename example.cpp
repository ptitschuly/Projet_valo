#include <iostream>
#include "european_option.h"
#include "american_option.h"
#include "greeks.h"
#include "monte_carlo.h"

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

    return 0;
}
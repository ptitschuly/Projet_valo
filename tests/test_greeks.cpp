#include "greeks.h"
#include <cassert>
#include <iostream>

void testGreeksCall() {
    Greeks g = GreeksCalculator::calculateEuropeanCall(100.0, 100.0, 1.0, 0.05, 0.2);
    std::cout << "Delta: " << g.delta << ", Gamma: " << g.gamma << ", Theta: " << g.theta
              << ", Vega: " << g.vega << ", Rho: " << g.rho << std::endl;
    assert(g.delta > 0 && g.delta < 1);
    assert(g.gamma > 0);
    assert(g.theta < 0);
    assert(g.vega > 0);
    assert(g.rho > 0);
}

void testGreeksPut() {
    Greeks g = GreeksCalculator::calculateEuropeanPut(100.0, 100.0, 1.0, 0.05, 0.2);
    std::cout << "Delta: " << g.delta << ", Gamma: " << g.gamma << ", Theta: " << g.theta
              << ", Vega: " << g.vega << ", Rho: " << g.rho << std::endl;
    assert(g.delta > -1 && g.delta < 0);
    assert(g.gamma > 0);
    assert(g.theta < 0);
    assert(g.vega > 0);
    assert(g.rho < 0);
}

int main() {
    testGreeksCall();
    testGreeksPut();
    std::cout << "All Greeks tests passed!" << std::endl;
    return 0;
}
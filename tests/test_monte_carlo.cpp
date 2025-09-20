#include "monte_carlo.h"
#include <cassert>
#include <iostream>

void testMonteCarloCall() {
    double price = MonteCarlo::priceOption(100.0, 100.0, 1.0, 0.05, 0.2, 10000, true);
    std::cout << "Monte Carlo Call Price: " << price << std::endl;
    assert(price > 0);
}

void testMonteCarloPut() {
    double price = MonteCarlo::priceOption(100.0, 100.0, 1.0, 0.05, 0.2, 10000, false);
    std::cout << "Monte Carlo Put Price: " << price << std::endl;
    assert(price > 0);
}
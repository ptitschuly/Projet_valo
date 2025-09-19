#include "black_scholes.h"
#include <cassert>
#include <iostream>

void testBlackScholesCall() {
    double price = BlackScholes::priceEuropeanCall(100.0, 100.0, 1.0, 0.05, 0.2);
    std::cout << "BS Call Price: " << price << std::endl;
    assert(price > 0 && price < 100);
}

void testBlackScholesPut() {
    double price = BlackScholes::priceEuropeanPut(100.0, 100.0, 1.0, 0.05, 0.2);
    std::cout << "BS Put Price: " << price << std::endl;
    assert(price > 0 && price < 100);
}

void testPutCallParity() {
    double S = 100.0, K = 100.0, T = 1.0, r = 0.05, sigma = 0.2;
    double call = BlackScholes::priceEuropeanCall(S, K, T, r, sigma);
    double put = BlackScholes::priceEuropeanPut(S, K, T, r, sigma);
    double parity = call - put - (S - K * exp(-r * T));
    std::cout << "Put-Call Parity check: " << parity << std::endl;
    assert(abs(parity) < 1e-6);
}

int main() {
    testBlackScholesCall();
    testBlackScholesPut();
    testPutCallParity();
    std::cout << "All Black-Scholes tests passed!" << std::endl;
    return 0;
}
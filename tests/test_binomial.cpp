#include "binomial_tree.h"
#include <cassert>
#include <iostream>

void testBinomialCall() {
    double price = BinomialTree::priceAmericanCall(100.0, 100.0, 1.0, 0.05, 0.2, 100);
    std::cout << "Binomial Call Price: " << price << std::endl;
    assert(price > 0);
}

void testBinomialPut() {
    double price = BinomialTree::priceAmericanPut(100.0, 100.0, 1.0, 0.05, 0.2, 100);
    std::cout << "Binomial Put Price: " << price << std::endl;
    assert(price > 0);
}
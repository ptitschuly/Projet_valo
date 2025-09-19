#include "european_option.h"
#include "american_option.h"
#include <cassert>
#include <iostream>

void testEuropeanCall() {
    EuropeanOption call("Test Call", 100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    double price = call.getPrice();
    std::cout << "European Call Price: " << price << std::endl;
    assert(price > 0);
}

void testEuropeanPut() {
    EuropeanOption put("Test Put", 100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    double price = put.getPrice();
    std::cout << "European Put Price: " << price << std::endl;
    assert(price > 0);
}

void testAmericanCall() {
    AmericanOption call("Test American Call", 100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    double price = call.getPrice();
    std::cout << "American Call Price: " << price << std::endl;
    assert(price > 0);
}

void testAmericanPut() {
    AmericanOption put("Test American Put", 100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
    double price = put.getPrice();
    std::cout << "American Put Price: " << price << std::endl;
    assert(price > 0);
}

int main() {
    testEuropeanCall();
    testEuropeanPut();
    testAmericanCall();
    testAmericanPut();
    std::cout << "All option tests passed!" << std::endl;
    return 0;
}
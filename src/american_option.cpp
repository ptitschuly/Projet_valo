#include "american_option.h"
#include "binomial_tree.h"

AmericanOption::AmericanOption(const std::string& name, double spotPrice, double strikePrice,
                               double timeToMaturity, double riskFreeRate, double volatility,
                               OptionType type)
    : Option(name, spotPrice, strikePrice, timeToMaturity, riskFreeRate, volatility, type, ExerciseType::American) {}

double AmericanOption::getPrice() const {
    int steps = 100;  // Default number of steps
    if (getType() == OptionType::Call) {
        return BinomialTree::priceAmericanCall(getSpotPrice(), getStrikePrice(),
                                                getTimeToMaturity(), getRiskFreeRate(), getVolatility(), steps);
    } else {
        return BinomialTree::priceAmericanPut(getSpotPrice(), getStrikePrice(),
                                               getTimeToMaturity(), getRiskFreeRate(), getVolatility(), steps);
    }
}
#include "european_option.h"
#include "black_scholes.h"

EuropeanOption::EuropeanOption(const std::string& name, double spotPrice, double strikePrice,
                               double timeToMaturity, double riskFreeRate, double volatility,
                               OptionType type)
    : Option(name, spotPrice, strikePrice, timeToMaturity, riskFreeRate, volatility, type, ExerciseType::European) {}

double EuropeanOption::getPrice() const {
    if (getType() == OptionType::Call) {
        return BlackScholes::priceEuropeanCall(getSpotPrice(), getStrikePrice(),
                                                getTimeToMaturity(), getRiskFreeRate(), getVolatility());
    } else {
        return BlackScholes::priceEuropeanPut(getSpotPrice(), getStrikePrice(),
                                               getTimeToMaturity(), getRiskFreeRate(), getVolatility());
    }
}
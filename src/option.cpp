#include "option.h"

Option::Option(const std::string& name, double spotPrice, double strikePrice,
               double timeToMaturity, double riskFreeRate, double volatility,
               OptionType type, ExerciseType exercise)
    : Instrument(name), spotPrice_(spotPrice), strikePrice_(strikePrice),
      timeToMaturity_(timeToMaturity), riskFreeRate_(riskFreeRate),
      volatility_(volatility), type_(type), exercise_(exercise) {}
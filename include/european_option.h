#pragma once

#include "option.h"

class EuropeanOption : public Option {
public:
    EuropeanOption(const std::string& name, double spotPrice, double strikePrice,
                   double timeToMaturity, double riskFreeRate, double volatility,
                   OptionType type);

    double getPrice() const override;
};
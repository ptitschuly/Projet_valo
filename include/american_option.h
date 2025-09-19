#pragma once

#include "option.h"

class AmericanOption : public Option {
public:
    AmericanOption(const std::string& name, double spotPrice, double strikePrice,
                   double timeToMaturity, double riskFreeRate, double volatility,
                   OptionType type);

    double getPrice() const override;
};
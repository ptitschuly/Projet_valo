#pragma once

#include "instrument.h"
#include <string>

enum class OptionType { Call, Put };
enum class ExerciseType { European, American };

class Option : public Instrument {
public:
    Option(const std::string& name, double spotPrice, double strikePrice,
           double timeToMaturity, double riskFreeRate, double volatility,
           OptionType type, ExerciseType exercise);

    virtual ~Option() = default;

    // Getters
    double getSpotPrice() const { return spotPrice_; }
    double getStrikePrice() const { return strikePrice_; }
    double getTimeToMaturity() const { return timeToMaturity_; }
    double getRiskFreeRate() const { return riskFreeRate_; }
    double getVolatility() const { return volatility_; }
    OptionType getType() const { return type_; }
    ExerciseType getExerciseType() const { return exercise_; }

protected:
    double spotPrice_;
    double strikePrice_;
    double timeToMaturity_;
    double riskFreeRate_;
    double volatility_;
    OptionType type_;
    ExerciseType exercise_;
};
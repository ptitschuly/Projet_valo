#pragma once

#include <functional>
#include <random>

class MonteCarlo {
public:
    static double priceOption(double S, double K, double T, double r, double sigma,
                              int numSimulations, bool isCall,
                              std::function<double(double)> payoff = nullptr);

private:
    static double generateGaussianNoise(std::mt19937& gen, std::normal_distribution<>& dist);
};
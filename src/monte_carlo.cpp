#include "monte_carlo.h"
#include <random>
#include <cmath>
#include <functional>

double MonteCarlo::priceOption(double S, double K, double T, double r, double sigma,
                               int numSimulations, bool isCall,
                               std::function<double(double)> payoff) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 1.0);

    double sum = 0.0;
    for (int i = 0; i < numSimulations; ++i) {
        double Z = generateGaussianNoise(gen, dist);
        double S_T = S * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * Z);
        double optionPayoff = payoff ? payoff(S_T) : (isCall ? std::max(S_T - K, 0.0) : std::max(K - S_T, 0.0));
        sum += optionPayoff;
    }

    double averagePayoff = sum / numSimulations;
    return exp(-r * T) * averagePayoff;
}

double MonteCarlo::generateGaussianNoise(std::mt19937& gen, std::normal_distribution<>& dist) {
    return dist(gen);
}
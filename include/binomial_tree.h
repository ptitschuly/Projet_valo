#pragma once

#include <vector>

class BinomialTree {
public:
    static double priceAmericanCall(double S, double K, double T, double r, double sigma, int steps);
    static double priceAmericanPut(double S, double K, double T, double r, double sigma, int steps);

private:
    static std::vector<std::vector<double>> buildTree(double S, double u, double d, int steps);
    static double calculateOptionValue(const std::vector<std::vector<double>>& tree,
                                       double K, double r, double dt, bool isCall, bool isAmerican);
};
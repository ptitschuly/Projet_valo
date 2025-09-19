#include "binomial_tree.h"
#include <vector>
#include <algorithm>
#include <cmath>

double BinomialTree::priceAmericanCall(double S, double K, double T, double r, double sigma, int steps) {
    double dt = T / steps;
    double u = exp(sigma * sqrt(dt));
    double d = exp(-sigma * sqrt(dt));
    double p = (exp(r * dt) - d) / (u - d);

    auto tree = buildTree(S, u, d, steps);
    return calculateOptionValue(tree, K, r, dt, true, true);
}

double BinomialTree::priceAmericanPut(double S, double K, double T, double r, double sigma, int steps) {
    double dt = T / steps;
    double u = exp(sigma * sqrt(dt));
    double d = exp(-sigma * sqrt(dt));
    double p = (exp(r * dt) - d) / (u - d);

    auto tree = buildTree(S, u, d, steps);
    return calculateOptionValue(tree, K, r, dt, false, true);
}

std::vector<std::vector<double>> BinomialTree::buildTree(double S, double u, double d, int steps) {
    std::vector<std::vector<double>> tree(steps + 1, std::vector<double>(steps + 1, 0.0));
    for (int i = 0; i <= steps; ++i) {
        for (int j = 0; j <= i; ++j) {
            tree[i][j] = S * pow(u, j) * pow(d, i - j);
        }
    }
    return tree;
}

double BinomialTree::calculateOptionValue(const std::vector<std::vector<double>>& tree,
                                          double K, double r, double dt, bool isCall, bool isAmerican) {
    int steps = tree.size() - 1;
    std::vector<double> values(steps + 1);

    // Terminal payoffs
    for (int j = 0; j <= steps; ++j) {
        double S_T = tree[steps][j];
        values[j] = isCall ? std::max(S_T - K, 0.0) : std::max(K - S_T, 0.0);
    }

    // Backward induction
    double discount = exp(-r * dt);
    for (int i = steps - 1; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            double continuation = discount * (0.5 * values[j] + 0.5 * values[j + 1]);
            double exercise = isCall ? std::max(tree[i][j] - K, 0.0) : std::max(K - tree[i][j], 0.0);
            values[j] = isAmerican ? std::max(continuation, exercise) : continuation;
        }
    }

    return values[0];
}
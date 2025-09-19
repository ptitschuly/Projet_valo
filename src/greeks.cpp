#include "greeks.h"
#include "black_scholes.h"
#include <cmath>

Greeks GreeksCalculator::calculateEuropeanCall(double S, double K, double T, double r, double sigma) {
    double d1_val = BlackScholes::d1(S, K, T, r, sigma);
    double d2_val = BlackScholes::d2(S, K, T, r, sigma);
    double N_d1 = BlackScholes::normalCDF(d1_val);
    double N_d2 = BlackScholes::normalCDF(d2_val);
    double n_d1 = exp(-0.5 * d1_val * d1_val) / sqrt(2 * M_PI);

    Greeks g;
    g.delta = N_d1;
    g.gamma = n_d1 / (S * sigma * sqrt(T));
    g.theta = - (S * sigma * n_d1) / (2 * sqrt(T)) - r * K * exp(-r * T) * N_d2;
    g.vega = S * sqrt(T) * n_d1;
    g.rho = K * T * exp(-r * T) * N_d2;

    return g;
}

Greeks GreeksCalculator::calculateEuropeanPut(double S, double K, double T, double r, double sigma) {
    double d1_val = BlackScholes::d1(S, K, T, r, sigma);
    double d2_val = BlackScholes::d2(S, K, T, r, sigma);
    double N_d1 = BlackScholes::normalCDF(d1_val);
    double N_d2 = BlackScholes::normalCDF(d2_val);
    double n_d1 = exp(-0.5 * d1_val * d1_val) / sqrt(2 * M_PI);

    Greeks g;
    g.delta = N_d1 - 1;
    g.gamma = n_d1 / (S * sigma * sqrt(T));
    g.theta = - (S * sigma * n_d1) / (2 * sqrt(T)) + r * K * exp(-r * T) * BlackScholes::normalCDF(-d2_val);
    g.vega = S * sqrt(T) * n_d1;
    g.rho = -K * T * exp(-r * T) * BlackScholes::normalCDF(-d2_val);

    return g;
}
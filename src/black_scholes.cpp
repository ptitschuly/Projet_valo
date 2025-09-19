#include "black_scholes.h"
#include <cmath>

double BlackScholes::priceEuropeanCall(double S, double K, double T, double r, double sigma) {
    double d1_val = d1(S, K, T, r, sigma);
    double d2_val = d2(S, K, T, r, sigma);
    return S * normalCDF(d1_val) - K * exp(-r * T) * normalCDF(d2_val);
}

double BlackScholes::priceEuropeanPut(double S, double K, double T, double r, double sigma) {
    double d1_val = d1(S, K, T, r, sigma);
    double d2_val = d2(S, K, T, r, sigma);
    return K * exp(-r * T) * normalCDF(-d2_val) - S * normalCDF(-d1_val);
}

double BlackScholes::normalCDF(double x) {
    return 0.5 * erfc(-x * sqrt(0.5));
}

double BlackScholes::d1(double S, double K, double T, double r, double sigma) {
    return (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
}

double BlackScholes::d2(double S, double K, double T, double r, double sigma) {
    return d1(S, K, T, r, sigma) - sigma * sqrt(T);
}
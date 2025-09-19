#pragma once

#include <cmath>

class BlackScholes {
public:
    static double priceEuropeanCall(double S, double K, double T, double r, double sigma);
    static double priceEuropeanPut(double S, double K, double T, double r, double sigma);

    // Helper functions
    static double normalCDF(double x);
    static double d1(double S, double K, double T, double r, double sigma);
    static double d2(double S, double K, double T, double r, double sigma);
};
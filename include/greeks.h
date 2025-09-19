#pragma once

struct Greeks {
    double delta;
    double gamma;
    double theta;
    double vega;
    double rho;
};

class GreeksCalculator {
public:
    static Greeks calculateEuropeanCall(double S, double K, double T, double r, double sigma);
    static Greeks calculateEuropeanPut(double S, double K, double T, double r, double sigma);
};
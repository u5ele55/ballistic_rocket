#pragma once
#include "Function/Function.hpp"

class AirDensityExponentialModel : public Function<double, double>
{
private:
    double p0;
    double H;
public:
    AirDensityExponentialModel(double p0 = 1300, double H = 8420);
    double operator()(double height);
};

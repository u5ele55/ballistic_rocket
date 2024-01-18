#pragma once
#include "InterpolatedFunction.hpp"

#include <vector>

class LinearInterpolatedFunction : public InterpolatedFunction
{
private: 
    bool allowExtrapolation;
public:
    LinearInterpolatedFunction(std::vector<double> x, std::vector<double> y, bool allowExtrapolation = false);
    double operator()(double t);
};
#pragma once
#include "InterpolatedFunction.hpp"

#include <vector>

class LinearInterpolatedFunction : public InterpolatedFunction
{
public:
    LinearInterpolatedFunction(std::vector<double> x, std::vector<double> y);
    double operator()(double t);
};
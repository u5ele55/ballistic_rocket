#pragma once
#include "InterpolatedFunction.hpp"
#include "LinearInterpolatedFunction.hpp"

class LinearInterpolationWithDiscontinuties : public InterpolatedFunction
{
private:
    std::vector<double> breaks;
    bool extrapolateToLeft;
public:
    LinearInterpolationWithDiscontinuties(
        std::vector<double> x, 
        std::vector<double> y, 
        std::vector<double> breaks,
        bool extrapolateToLeft = true
    );

    double operator()(double t);
};
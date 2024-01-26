#pragma once
#include "LinearInterpolatedFunction.hpp"
#include "ConditionalInterpolation.hpp"

class ConditionalLinearInterpolation : public ConditionalInterpolation
{
public:
    ConditionalLinearInterpolation(
        std::vector<double> conditions,
        std::vector<double> x,
        std::vector<std::vector<double>> y,
        bool allowExtrapolation = false);
    InterpolatedFunction& operator()(double h);
    ~ConditionalLinearInterpolation() {};
};
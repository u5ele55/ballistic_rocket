#pragma once
#include "Function/Function.hpp"

#include <vector>

class InterpolatedFunction : public Function<double, double>
{
protected:
    int gridSize;
    std::vector<std::pair<double, double>> grid;
public:
    /// @brief This class will interpolate values between between x's where it isn't defined in given grid
    /// @param x coordinates where function is known. should be sorted in ascending order
    /// @param y y(x)
    InterpolatedFunction(std::vector<double> x, std::vector<double> y);
    virtual double operator()(double t) = 0;
};
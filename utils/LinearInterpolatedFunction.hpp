#pragma once
#include "Function.hpp"

#include <vector>

class LinearInterpolatedFunction : Function<double, double>
{
private:
    int gridSize;
    std::vector<std::pair<double, double>> grid;
public:
    /// @brief This function will interpolate values between between x's where it isn't defined in given grid
    /// @param x coordinates where function is known. should be sorted in ascending order
    /// @param y y(x)
    LinearInterpolatedFunction(std::vector<double> x, std::vector<double> y);
    double operator()(double t);
};
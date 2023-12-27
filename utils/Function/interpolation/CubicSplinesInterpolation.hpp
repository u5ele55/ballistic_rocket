#pragma once

#include "InterpolatedFunction.hpp"
#include <vector>
#include "../../Vector.hpp"

class CubicSplinesInterpolation : public InterpolatedFunction
{
protected:
    std::vector<Vector> coefs;
    std::vector<double> y_near;
    std::vector<double> a;
public:
    /// @brief Cubic Splines method for interpolation
    /// @param x x-values in ascending order
    /// @param y y(x)
    /// @param coefs 4x4 matrix representing coeffitients for values of a function
    CubicSplinesInterpolation(std::vector<double> x, std::vector<double> y, 
        std::vector<Vector> coefs = {
            {-1, 1, -1, 1},
            {2, -2, 1, -1},
            {-1, 0, 1, 0},
            {0, 1, 0, 0}
        });
    double operator()(double t);
};

class CatmullRomSplineInterpolation : public CubicSplinesInterpolation 
{
public:
    CatmullRomSplineInterpolation(std::vector<double> x, std::vector<double> y)
        : CubicSplinesInterpolation(x,y, 
        {
            {-0.5, 1.5, -1.5, 0.5},
            {1, -2.5, 2, -0.5},
            {-0.5, 0, 0.5, 0},
            {0, 1, 0, 0}
        }) {};
};
#pragma once 

#include "../utils/Function/Function.hpp"
#include <string>

class FunctionCreator
{
private:
    /* data */
public:
    Function<double, double> createLinearInterpolator(const std::string& filename);
    Function<double, double> createCubicSplineInterpolator(const std::string& filename);
    Function<double, double> createCatmullRomSplineInterpolator(const std::string& filename);
};

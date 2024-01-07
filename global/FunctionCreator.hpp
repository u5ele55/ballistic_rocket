#pragma once 

#include "../utils/Function/Function.hpp"
#include <string>
#include <vector>

class FunctionCreator
{
private:
    std::pair<std::vector<double>, std::vector<double>> extractXY(const std::string& filename);
public:
    Function<double, double> *createLinearInterpolator(const std::string& filename);
    Function<double, double> *createCubicSplineInterpolator(const std::string& filename);
    Function<double, double> *createCatmullRomSplineInterpolator(const std::string& filename);
};

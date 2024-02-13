#pragma once

#include <string>
#include <vector>
#include "Function/Function.hpp"
#include "Function/interpolation/ConditionalLinearInterpolation.hpp"

class FunctionCreator
{
private:
    std::pair<std::vector<double>, std::vector<double>> extractXY(const std::string& filename);
public:
    Function<double, double> *createLinearInterpolator(const std::string& filename, bool allowExtrapolation = false);
    Function<double, double> *createDiscontinuityLinearInterpolator(const std::string& filename, std::vector<double> breaks);
    Function<double, double> *createCubicSplineInterpolator(const std::string& filename);
    Function<double, double> *createCatmullRomSplineInterpolator(const std::string& filename);
    ConditionalLinearInterpolation *createConditionalLinearInterpolator(const std::string& filename, bool allowExtrapolation = false);
};

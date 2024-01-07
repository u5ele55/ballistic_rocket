#include "FunctionCreator.hpp"

#include "../utils/function/interpolation/LinearInterpolatedFunction.hpp"
#include "../utils/function/interpolation/CubicSplinesInterpolation.hpp"

#include <fstream>


std::pair<std::vector<double>, std::vector<double>> FunctionCreator::extractXY(const std::string &filename)
{
    std::ifstream file(filename);

    int N;
    file >> N;

    std::vector<double> x(N);
    std::vector<double> y(N);
    for(int i = 0; i < N; i ++) {
        file >> x[i] >> y[i];
    }
    file.close();

    return {x, y};
}

Function<double, double> *FunctionCreator::createLinearInterpolator(const std::string &filename)
{
    auto xy = extractXY(filename);
    LinearInterpolatedFunction *fun = new LinearInterpolatedFunction(xy.first, xy.second);

    return fun;
}

Function<double, double> *FunctionCreator::createCubicSplineInterpolator(const std::string &filename)
{
    auto xy = extractXY(filename);
    CubicSplinesInterpolation *fun = new CubicSplinesInterpolation(xy.first, xy.second);

    return fun;
}

Function<double, double> *FunctionCreator::createCatmullRomSplineInterpolator(const std::string &filename)
{
    auto xy = extractXY(filename);
    CatmullRomSplineInterpolation *fun = new CatmullRomSplineInterpolation(xy.first, xy.second);

    return fun;
}
#include "FunctionCreator.hpp"

#include "../utils/Function/interpolation/LinearInterpolatedFunction.hpp"
#include "../utils/Function/interpolation/LinearInterpolationWithDiscontinuties.hpp"
#include "../utils/Function/interpolation/CubicSplinesInterpolation.hpp"

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

Function<double, double> *FunctionCreator::createLinearInterpolator(const std::string &filename, bool allowExtrapolation)
{
    auto xy = extractXY(filename);
    LinearInterpolatedFunction *fun = new LinearInterpolatedFunction(xy.first, xy.second, allowExtrapolation);

    return fun;
}

Function<double, double> *FunctionCreator::createDiscontinuityLinearInterpolator(const std::string &filename, std::vector<double> breaks)
{
    auto xy = extractXY(filename);
    auto *fun = new LinearInterpolationWithDiscontinuties(xy.first, xy.second, breaks);

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

ConditionalLinearInterpolation *FunctionCreator::createConditionalLinearInterpolator(const std::string &filename, bool allowExtrapolation)
{
    std::ifstream file(filename);

    int M;
    file >> M;

    std::vector<double> conds(M);
    for(int i = 0; i < M; i ++) {
        file >> conds[i];
    }
    
    int N;
    file >> N;

    std::vector<double> x(N);
    for(int i = 0; i < N; i ++) {
        file >> x[i];
    }
    std::vector<std::vector<double>> y(M, std::vector<double>(N));
    for (int j = 0; j < N; j ++) {
        for(int i = 0; i < M; i ++)
            file >> y[i][j];
    }
    file.close();

    ConditionalLinearInterpolation *fun = new ConditionalLinearInterpolation(conds, x, y, allowExtrapolation);

    return fun;
}

#include "InterpolatedFunction.hpp"

InterpolatedFunction::InterpolatedFunction(std::vector<double> x, std::vector<double> y)
    : gridSize(x.size())
{
    for (int i = 0; i < gridSize; i ++) {
        grid.emplace_back(x[i], y[i]);
    }
}
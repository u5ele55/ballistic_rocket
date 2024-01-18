#include "LinearInterpolatedFunction.hpp"

#include <stdexcept>

LinearInterpolatedFunction::LinearInterpolatedFunction(
    std::vector<double> x, 
    std::vector<double> y, 
    bool allowExtrapolation)
    : InterpolatedFunction(x, y),
    allowExtrapolation(allowExtrapolation) {}

double LinearInterpolatedFunction::operator()(double t)
{
    // bin search for x[i] < t < x[i+1]
    if (!allowExtrapolation && (t < grid[0].first || t > grid[gridSize - 1].first)) {
        throw std::runtime_error("t is out of range of interpolation");
    }
    int l = 0, r = gridSize, mid;

    while (r - l > 1) {
        mid = (r+l) / 2;
        if (grid[mid].first < t) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if (r == gridSize) {
        // extrapolate to right
        r --;
        l --;
    } else if (r == 0) {
        // extrapolate to left
        l ++;
        r ++;
    }
    
    double x1 = grid[l].first, x2 = grid[r].first;
    double y1 = grid[l].second, y2 = grid[r].second;

    return (y2-y1) / (x2-x1) * (t - x1) + y1;
}

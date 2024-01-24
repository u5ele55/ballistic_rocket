#include "LinearInterpolationWithDiscontinuties.hpp"

#include <stdexcept>

LinearInterpolationWithDiscontinuties::LinearInterpolationWithDiscontinuties(
    std::vector<double> x, 
    std::vector<double> y, 
    std::vector<double> breaks,
    bool extrapolateToLeft
)
: InterpolatedFunction(x, y), breaks(breaks), extrapolateToLeft(extrapolateToLeft)
{
    if (breaks[breaks.size() - 1] >= x[x.size()-1]) {
        throw std::runtime_error("LinearInterpolationWithDiscontinuties: breakpoints should be less than last x");
    }
}

double LinearInterpolationWithDiscontinuties::operator()(double t)
{
    // bin search for x[i] < t < x[i+1]
    int l = 0, r = gridSize, mid;

    while (r - l > 1) {
        mid = (r+l) / 2;
        if (grid[mid].first < t) {
            l = mid;
        } else {
            r = mid;
        }
    }

    for(int i = 0; i < breaks.size(); i ++) {
        if (breaks[i] < grid[r].first) {
            if (breaks[i] < grid[r].first)
        }
    }
}

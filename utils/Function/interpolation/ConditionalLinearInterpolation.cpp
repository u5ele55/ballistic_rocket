#include "ConditionalLinearInterpolation.hpp"

#include <stdexcept>

ConditionalLinearInterpolation::ConditionalLinearInterpolation(std::vector<double> conditions, std::vector<double> x, std::vector<std::vector<double>> y, bool allowExtrapolation)
{
    if (conditions.size() != y.size() || x.size() != y[0].size()) {
        throw std::runtime_error("Size mismatch for conditional interpolation");
    }
    for (int i = 0; i < y.size(); i ++) {
        use.emplace_back(conditions[i], new LinearInterpolatedFunction(x, y[i], allowExtrapolation));
    }
}

// returns linearly interpolated function depends on h
InterpolatedFunction &ConditionalLinearInterpolation::operator()(double h)
{
    int l = 0, r = use.size()-1, mid;

    while (r - l > 1) {
        mid = (r+l) / 2;
        if (use[mid].first > h) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if (use[r].first < h)
        l = r;
    InterpolatedFunction *a = (use[l].second);
    return *a;
}


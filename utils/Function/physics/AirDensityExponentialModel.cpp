#include "AirDensityExponentialModel.hpp"

#include <cmath>

AirDensityExponentialModel::AirDensityExponentialModel(double p0, double H)
    : p0(p0), H(H) {}

double AirDensityExponentialModel::operator()(double height)
{
    return p0 * exp(-height / H);
}
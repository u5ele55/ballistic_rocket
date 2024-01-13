#pragma once
#include "ISystem.hpp"
#include "Parameters.hpp"
#include "../../utils/function/Function.hpp"

class BR2DFlatEarth : public ISystem
{
private:
    Vector initialState;
    Parameters *params;

    Function<double, double> *power;
    Function<double, double> *mass;
    Function<double, double> *pitchAngle;
public:
    BR2DFlatEarth(Parameters * params, double x, double y, double vx, double vy);
    void f(Vector &state, double time) const;
    Vector getInitialState() const;
}; 
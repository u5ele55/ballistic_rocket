#pragma once
#include "ISystem.hpp"

#include "../../utils/function/Function.hpp"

class BR2DFlatEarth : public ISystem
{
private:
    Vector initialState;
    double startHeight;
    double activeTime;

    Function<double, double> *power;
    Function<double, double> *mass;
    Function<double, double> *pitchAngle;
public:
    BR2DFlatEarth(double height, double x, double y, double vx, double vy, double activeTime);
    void f(Vector &state, double time) const;
    Vector getInitialState() const;
};
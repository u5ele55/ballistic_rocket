#include "BR2DFlatEarth.hpp"
#include "../../global/GlobalScope.hpp"

#include <cmath>

BR2DFlatEarth::BR2DFlatEarth(double height, double x, double y, double vx, double vy, double activeTime)
    : startHeight(height),
    activeTime(activeTime),
    initialState({x, y, vx, vy})
{
    auto &scope = GlobalScope::getInstance();

    power = &scope.getPowerEvaluator();
    pitchAngle = &scope.getPitchAngleEvaluator();
    mass = &scope.getMassEvaluator();
}

void BR2DFlatEarth::f(Vector &state, double time) const
{
    double x = state[0], y = state[1];
    double vx = state[2], vy = state[3];

    state[0] = vx;
    state[1] = vy;

    double P = 9.81 * (*power)(time);
    double m = (*mass)(time);
    double theta = (*pitchAngle)(time) * M_PI / 180;

    state[2] = P / m * cos(theta);
    state[3] = P / m * sin(theta) - 9.81;
}

Vector BR2DFlatEarth::getInitialState() const
{
    return initialState;
}

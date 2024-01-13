#include "BR2DFlatEarth.hpp"
#include "../../global/GlobalScope.hpp"

#include <cmath>

BR2DFlatEarth::BR2DFlatEarth(Parameters *params, double x, double y, double vx, double vy)
    : params(params),
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

    // Passive arc
    if (time > params->stageEndtime.third) {
        // TODO: just drag and gravitational forces
        state[2] = 0;
        state[3] = 0;
        return;
    }    

    // TODO: Change 9.81 to G*Me*<component> / r**3 
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

#include "BR2DFlatEarth.hpp"
#include "../../global/GlobalScope.hpp"
#include "../../global/Constants.hpp"

#include <cmath>

BR2DFlatEarth::BR2DFlatEarth(Parameters *params, double x, double y, double vx, double vy)
    : params(params),
    initialState({x, y, vx, vy})
{
    auto &scope = GlobalScope::getInstance();

    power = &scope.getPowerEvaluator();
    pitchAngle = &scope.getPitchAngleEvaluator();
    mass = &scope.getMassEvaluator();
    atmosphere = &scope.getAtmosphereParamsEvaluator();

    endMass = (*mass)(params->stageEndtime.third);

    Cx_1 = &scope.getDragCoef1Evaluator();
    Cx_2 = &scope.getDragCoef2Evaluator();
    Cx_W = &scope.getDragCoefWarheadEvaluator();
}
#include <iostream>
void BR2DFlatEarth::f(Vector &state, double time) const
{
    double drag = 0;
    double x = state[0], y = state[1];
    double vx = state[2], vy = state[3];

    double v_sqr = vx*vx + vy*vy;
    double v = sqrt(v_sqr);

    double height = y; // Change later for ellipse model
    if (height < 0) {
        state = {0, 0, 0, 0};
        return;
    }
    auto atm = (*atmosphere)(height);
    double M = sqrt(v_sqr) / atm.soundSpeed; // mach value

    state[0] = vx;
    state[1] = vy;

    double gravitationalForceY = Constants::Common::G * Constants::Earth::MASS / (pow(Constants::Earth::MAJOR_AXIS, 2) + y*y);

    // Passive arc
    if (time > params->stageEndtime.third) {
        if (height < 1200000) {
            double Cd = (*Cx_W)(M);
            // TODO: midel area 2 - change to midel for warhead
            drag = 0.5 * atm.density * params->missile.midelArea2 * Cd * v_sqr;
        }
        state[2] = -drag / endMass * vx / v;
        state[3] = -drag / endMass * vy / v - gravitationalForceY;
        return;
    }
    else if (time > params->stageEndtime.second) {
        // third stage
    }
    else if (time > params->stageEndtime.first) {
        // second stage
        double Cd = (*Cx_2)(height)(M);
        drag = 0.5 * atm.density * params->missile.midelArea2 * Cd * v_sqr;
    }
    else {
        // first stage
        // std::cout << "M: " << M << " h: " << height << " ss: " << atm.soundSpeed << " v: " << vx << ", " << vy << '\n';
        double Cd = (*Cx_1)(height)(M);
        drag = 0.5 * atm.density * params->missile.midelArea1 * Cd * v_sqr;
    }
    
    // TODO: Change 9.81 to G*Me*<component> / r**3 
    double P = 9.81 * (*power)(time);
    double m = (*mass)(time);
    double theta = (*pitchAngle)(time) * M_PI / 180;
    // std::cout << "Drag: " << drag << " g: " << gravitationalForceY << '\n';
    state[2] = (P * cos(theta) - drag  * vx / v) / m;
    state[3] = (P * sin(theta) - drag  * vy / v) / m - gravitationalForceY;
}

Vector BR2DFlatEarth::getInitialState() const
{
    return initialState;
}

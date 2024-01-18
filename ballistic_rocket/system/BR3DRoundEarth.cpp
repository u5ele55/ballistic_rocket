#include "BR3DRoundEarth.hpp"
#include "../../global/GlobalScope.hpp"
#include "../../global/Constants.hpp"

#include <cmath>

BR3DRoundEarth::BR3DRoundEarth(Parameters *params, Vector initialCoordinates, Vector initialVelocity)
    : params(params),
    initialState({
        initialCoordinates[0], 
        initialCoordinates[1], 
        initialCoordinates[2], 
        initialVelocity[0], 
        initialVelocity[1], 
        initialVelocity[2]})
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
void BR3DRoundEarth::f(Vector &state, double time) const
{
    double drag = 0;
    double x = state[0], y = state[1], z = state[2];
    double vx = state[3], vy = state[4], vz = state[5];

    double v_sqr = vx*vx + vy*vy + vz*vz;
    double v = sqrt(v_sqr);

    double Re = Constants::Earth::MAJOR_AXIS;

    double r_sqr = x*x + y*y + z*z;
    double height_sqr = r_sqr - Re*Re; // Change later for ellipse model
    if (height_sqr < 0) {
        state = {0, 0, 0, 0, 0, 0};
        return;
    }
    double height = sqrt(height_sqr);
    auto atm = (*atmosphere)(height);
    double M = sqrt(v_sqr) / atm.soundSpeed; // mach value

    state[0] = vx;
    state[1] = vy;
    state[2] = vz;

    auto gravitationalForce = Vector{x, y, z} * (Constants::Common::G * Constants::Earth::MASS / pow(r_sqr, 1.5));

    // Passive arc
    if (time > params->stageEndtime.third) {
        if (height < 1200000) {
            double Cd = (*Cx_W)(M);
            // TODO: midel area 2 - change to midel for warhead
            drag = 0.5 * atm.density * params->missile.midelArea2 * Cd * v_sqr;
        }
        state[3] = -drag / endMass * vx / v - gravitationalForce[0];
        state[4] = -drag / endMass * vy / v - gravitationalForce[1];
        state[5] = -drag / endMass * vz / v - gravitationalForce[2];
        return;
    }
    else if (time > params->stageEndtime.second) {
        // third stage
    }
    else if (time > params->stageEndtime.first) {
        // second stage
        // std::cout << "time: " << time << " M: " << M << " h: " << height << " ss: " << atm.soundSpeed << " v: " << vx << ", " << vy << '\n';
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
    state[3] = (P * cos(theta) - drag  * vx / v) / m - gravitationalForce[0];
    state[4] = (P * sin(theta) - drag  * vy / v) / m - gravitationalForce[1];
    state[5] = (- drag  * vz / v) / m - gravitationalForce[2];
}

Vector BR3DRoundEarth::getInitialState() const
{
    return initialState;
}

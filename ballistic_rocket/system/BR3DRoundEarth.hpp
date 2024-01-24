#pragma once
#include "ISystem.hpp"
#include "Parameters.hpp"
#include "../../utils/Function/Function.hpp"
#include "../../utils/Function/physics/AtmosphereParameters.hpp"

class BR3DRoundEarth : public ISystem
{
private:
    Vector initialState;
    Parameters *params;

    Function<double, double> *power;
    Function<double, double> *mass;
    Function<double, double> *pitchAngle;

    Function<double, AtmosphereParameters> *atmosphere;

    Function<double, Function<double, double>&> *Cx_1;
    Function<double, Function<double, double>&> *Cx_2;
    Function<double, double> *Cx_W;

    double endMass;
    Vector fromStartToNorth;
public:
    BR3DRoundEarth(Parameters * params, Vector initialCoordinates, Vector initialVelocity);
    void f(Vector &state, double time) const;
    Vector getInitialState() const;
}; 
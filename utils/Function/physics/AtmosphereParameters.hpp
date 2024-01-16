#pragma once
#include "../Function.hpp"

struct AtmosphereParameters {
    double density;
    double soundSpeed;
    double temperature;
    double pressure;
};

class StandartAtmosphereParameters : public Function<double, AtmosphereParameters>
{
public:
    AtmosphereParameters operator()(double h);
    StandartAtmosphereParameters();
};

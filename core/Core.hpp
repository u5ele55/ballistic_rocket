#pragma once

#include "Vector.hpp"
#include "file_input/ParametersInputter.hpp"
#include "ballistic_rocket/modeling/AbstractSolver.hpp"

class Core
{
private:
    Parameters * params;
    Vector startBLH;
    AbstractSolver * solver;
    ISystem * model;
    double flightTime;
public:
    Core();

    Vector calculateEndpoint();
    std::vector<std::pair<double, double>> heights(int points = 100);
    Vector getStartBLH() const;
    double getFlightTime() const;

    ~Core();
};

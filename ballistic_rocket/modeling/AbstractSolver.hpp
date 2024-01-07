#pragma once

#include "../system/ISystem.hpp"

class AbstractSolver {
public:
    explicit AbstractSolver(ISystem *system, double step = 0.01);

    virtual void methodStep(Vector &state, double step, double time) = 0;

    Vector solve(double time); 

    virtual ~AbstractSolver() = default;

protected:
    ISystem *system;
    double step;
    std::vector<Vector> states;
};
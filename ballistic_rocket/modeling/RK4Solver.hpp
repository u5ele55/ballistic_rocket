#pragma once

#include "AbstractSolver.hpp"

class RK4Solver : public AbstractSolver {
public:
    explicit RK4Solver(ISystem *system, double step = 1e-2);

    void methodStep(Vector &state, double step, double time) final;

    ~RK4Solver() = default;

private:
    Vector k1, k2, k3, k4;
};
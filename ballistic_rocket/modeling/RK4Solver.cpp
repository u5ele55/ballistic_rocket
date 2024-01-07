#include "RK4Solver.hpp"

RK4Solver::RK4Solver(ISystem *system, double step)
    : AbstractSolver(system, step),
        k1(states[0].size()),
        k2(states[0].size()),
        k3(states[0].size()),
        k4(states[0].size()) {}

void RK4Solver::methodStep(Vector &state, double step, double time) {
    k1 = state;
    system->f(k1, time);

    //k2 = state + k1 * (step / 2);
    for(int i = 0; i < k2.size(); i ++) {
        k2[i] = state[i] + k1[i] * step / 2;
    }
    
    system->f(k2, time);

    //k3 = state + k2 * (step / 2);
    for(int i = 0; i < k3.size(); i ++) {
        k3[i] = state[i] + k2[i] * step / 2;
    }
    system->f(k3, time);

    //k4 = state + k3 * step;
    for(int i = 0; i < k4.size(); i ++) {
        k4[i] = state[i] + k3[i] * step;
    }
    system->f(k4, time);

    //state += (k1 + k2 * 2 + k3 * 2 + k4) * (step / 6);
    for(int i = 0; i < k1.size(); i ++) {
        state[i] = state[i] + (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]) * step / 6;
    }
}
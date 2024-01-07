#include "AbstractSolver.hpp"

AbstractSolver::AbstractSolver(ISystem *system, double step)
    : system(system), step(step) {
        states.push_back(system->getInitialState());
    }

Vector AbstractSolver::solve(double time)
{
    if (system == nullptr) {
        return Vector(0);
    }
    Vector state(states[0].size());
    int stepsInTime = static_cast<int>(time / step);

    if (time < (states.size() - 1) * step) {
        state = states[stepsInTime];
    } else {
        state = states[states.size() - 1];
        for(int _ = states.size() - 1; _ < stepsInTime; _++) {
            methodStep(state, step, _ * step);
            states.push_back(state);
        }
    }

    // recalculate more precisely for case when t != step * k for some whole k
    double wholePart = step * stepsInTime;
    double timeDiff = time - wholePart;

    if (timeDiff != 0) {
        methodStep(state, timeDiff, time);
    }

    return state;
}
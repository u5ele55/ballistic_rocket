#include <iostream>
#include "utils/Vector.hpp"
#include "ballistic_rocket/modeling/RK4Solver.hpp"
#include "ballistic_rocket/system/BR2DFlatEarth.hpp"
#include "global/GlobalScope.hpp"
#include <vector>
#include <fstream>

int main() {
    BR2DFlatEarth *model = new BR2DFlatEarth(100, 0, 0, 0, 8, 175);
    RK4Solver solver(model);

    double step = 2;
    std::ofstream file("trajectory.txt");

    for (int i = 0; i < 175.001; i += step) {
        const auto &state = solver.solve(i);
        file << i << ' ' << state[0] << ' ' << state[1] << '\n';
    }
    file.close();

    delete model;

    return 0;
}
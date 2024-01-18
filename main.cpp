#include <iostream>
#include <vector>

#include "utils/Vector.hpp"
#include "ballistic_rocket/modeling/RK4Solver.hpp"
#include "ballistic_rocket/system/BR2DFlatEarth.hpp"
#include "global/GlobalScope.hpp"
#include "utils/file_input/ParametersInputter.hpp"
#include "utils/file_input/filenames.hpp"

#include "utils/Function/physics/AtmosphereParameters.hpp"

int main() {
    ParametersInputter paramsCreator(FILENAMES.at("parameters"));
    Parameters * params = paramsCreator.create();
    BR2DFlatEarth *model = new BR2DFlatEarth(params, 0, params->setup.height, 0, params->setup.velocity);
    RK4Solver solver(model);

    double step = 2, time = 0;
    std::ofstream file("trajectory.txt");
    auto state = solver.solve(0);
    auto lastState = Vector{};
    while (state[1] > 0 && step > 0.001) {
        state = solver.solve(time);
        if (state[1] > 0) {
            file << time << ' ' << state[0] << ' ' << state[1] << '\n';
        }
        std::cout << time << "ok\n";
        time += step;
    }
    // todo: bin search for missile fall time 

    file.close();

    delete model;
    delete params;
    std::cout << "done\n";

    return 0;
}
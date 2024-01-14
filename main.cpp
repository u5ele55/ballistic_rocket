#include <iostream>
#include <vector>

#include "utils/Vector.hpp"
#include "ballistic_rocket/modeling/RK4Solver.hpp"
#include "ballistic_rocket/system/BR2DFlatEarth.hpp"
#include "global/GlobalScope.hpp"
#include "utils/file_input/ParametersInputter.hpp"
#include "utils/file_input/filenames.hpp"

int main() {
    FunctionCreator creator;
    ConditionalLinearInterpolation *confun = creator.createConditionalLinearInterpolator(FILENAMES.at("Cx_1"));
    std::cout << "created\n";
    auto &fun = (*confun)(50000);
    std::cout << "conds\n";
    std::cout << fun(3.95);

    exit(0);

    ParametersInputter paramsCreator(FILENAMES.at("parameters"));
    Parameters * params = paramsCreator.create();
    BR2DFlatEarth *model = new BR2DFlatEarth(params, 0, params->setup.height, 0, params->setup.velocity);
    RK4Solver solver(model);

    double step = 2;
    std::ofstream file("trajectory.txt");

    for (int i = 0; i < 175.001; i += step) {
        const auto &state = solver.solve(i);
        file << i << ' ' << state[0] << ' ' << state[1] << '\n';
    }
    file.close();

    delete model;
    delete params;
    std::cout << "done\n";

    return 0;
}
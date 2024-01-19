#include <iostream>
#include <vector>

#include "utils/Vector.hpp"
#include "utils/LinAlg.hpp"
#include "ballistic_rocket/modeling/RK4Solver.hpp"
#include "ballistic_rocket/system/BR3DRoundEarth.hpp"
#include "utils/file_input/ParametersInputter.hpp"
#include "utils/file_input/filenames.hpp"

#include "global/GlobalScope.hpp"
#include "global/Constants.hpp"

int main() {
    ParametersInputter paramsCreator(FILENAMES.at("parameters"));
    Parameters * params = paramsCreator.create();


    Vector testCoord = {0, Constants::Earth::MAJOR_AXIS + params->setup.height, 0};
    Vector testVelocity = {0, params->setup.velocity, 0};
    
    testCoord = LinAlg::rotateAbout(testCoord, {0, 0, 1}, M_PI / 6);
    testCoord = LinAlg::rotateAbout(testCoord, {1, 0, 0}, M_PI / 4);
    
    testVelocity = LinAlg::rotateAbout(testVelocity, {0, 0, 1}, M_PI / 6);
    testVelocity = LinAlg::rotateAbout(testVelocity, {1, 0, 0}, M_PI / 4);

    std::cout << testCoord << " " << testVelocity << '\n';

    BR3DRoundEarth *model = new BR3DRoundEarth(params, testCoord, testVelocity);
    RK4Solver solver(model);

    double step = 2, time = 2;
    std::ofstream file("trajectory.txt");
    auto state = solver.solve(0);
    auto lastState = Vector(state.size());

    while ((state - lastState).norm() > 0.01 && step > 0.001) {
        lastState = state;
        try {
            state = solver.solve(time);
        } catch (const std::exception &e) {
            std::cout << e.what() << '\n';
            break;
        }
        file << time << ' ' << state[0] << ' ' << state[1] << ' ' << state[2] << '\n';
        
        std::cout << time << " " << state << "ok\n";
        time += step;
    }
    // todo: bin search for missile fall time 

    file.close();

    delete model;
    delete params;
    std::cout << "done\n";

    return 0;
}
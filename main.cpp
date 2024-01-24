#include <iostream>
#include <vector>

#include "utils/Vector.hpp"
#include "utils/LinAlg.hpp"
#include "utils/coordinates.hpp"
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

    Vector blhStart = {params->setup.latitude, params->setup.longitude, params->setup.height};
    Vector y_prime = blh2ecef(blhStart);
    std::cout << blhStart << '=' << ecef2blh(y_prime) << '\n';
    // Vector y_proj = LinAlg::projectionOnPlane(y_prime, {1,0,0}, {0,1,0});

    // double angle = LinAlg::angle({0,1,0}, y_proj);
    // Vector x_prime = LinAlg::rotateAbout({1,0,0}, {0,0,1}, angle);
    
    // testVelocity = LinAlg::rotateAbout(testVelocity, {0, 0, 1}, angle);
    // std::cout << LinAlg::angle(y_prime, y_proj) << '=' << LinAlg::angle(y_prime, testVelocity) << '\n';
    
    // testVelocity = LinAlg::rotateAbout(testVelocity, x_prime, LinAlg::angle(y_prime, y_proj));
    
    testVelocity = LinAlg::rotateAbout(testVelocity, {1,0,0}, params->setup.latitude);
    testVelocity = LinAlg::rotateAbout(testVelocity, {0,0,1}, params->setup.longitude - M_PI_2);

    std::cout << y_prime << " " << testVelocity << '\n';

    BR3DRoundEarth *model = new BR3DRoundEarth(params, y_prime, testVelocity); // todo: cahnge testcoord to y_prime
    RK4Solver solver(model);

    double step = 2, time = 0;
    std::ofstream file("trajectory.txt");
    auto state = solver.solve(time);
    auto lastState = Vector(state.size());

    while ((state - lastState).norm() > 0.01) {
        lastState = state;
        time += step;
        try {
            state = solver.solve(time);
        } catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << '\n';
            break;
        }
        file << time << ' ' << state[0] << ' ' << state[1] << ' ' << state[2] << '\n';
        
        // std::cout << time << " " << state << "ok\n" << lastState << '\n';
    }
    // todo: bin search for missile fall time 
    blhStart[0] *= 180 / M_PI;
    blhStart[1] *= 180 / M_PI;
    Vector blhEnd = ecef2blh(state);
    blhEnd[0] *= 180 / M_PI;
    blhEnd[1] *= 180 / M_PI;
    std::cout << "Start point: " << blhStart
              << "\nEnd point: " << blhEnd << '\n';

    file.close();

    delete model;
    delete params;

    std::cout << "done\n";

    return 0;
}
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

    Vector blhStart = {params->setup.latitude, params->setup.longitude, params->setup.height};
    Vector coordinate = blh2ecef(blhStart);
    
    Vector velocity = {0, params->setup.velocity, 0};
    velocity = LinAlg::rotateAbout(velocity, {1,0,0}, params->setup.latitude);
    velocity = LinAlg::rotateAbout(velocity, {0,0,1}, params->setup.longitude - M_PI_2);

    BR3DRoundEarth *model = new BR3DRoundEarth(params, coordinate, velocity); 
    RK4Solver solver(model, 3e-3);

    std::ofstream file("trajectory.txt");
    double step = 2, time = 0;
    auto state = solver.solve(time);
    auto lastState = Vector(state.size());

    while ((state - lastState).norm() > 0.01) {
        file << time << ' ' << state[0] << ' ' << state[1] << ' ' << state[2] << '\n';
        time += step;
        lastState = state;
        try {
            state = solver.solve(time);
        } catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << '\n';
            break;
        }
        // std::cout << time << " " << state << "ok\n" << lastState << '\n';
    }
    double r_time = time-step, l_time = time - 2*step;
    while (r_time - l_time > 1e-6) {
        
        double mid = (r_time + l_time) / 2;
        state = solver.solve(mid);
        if ((state - lastState).norm() < 0.001) {
            r_time = mid;
        } else {
            l_time = mid;
        }
    }
    std::cout << "Flight time: " << r_time << " s. \n";
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

    std::cout << "\nFinished.\n";

    return 0;
}
#include "Core.hpp"

#include "utils/file_input/filenames.hpp"
#include "utils/coordinates.hpp"
#include "utils/LinAlg.hpp"

#include "ballistic_rocket/modeling/RK4Solver.hpp"
#include "ballistic_rocket/system/BR3DRoundEarth.hpp"

#include "global/GlobalScope.hpp"
#include "global/Constants.hpp"

#include <cmath>
#include <iostream>

Core::Core()
    : startBLH(3),
    flightTime(0),
    model(nullptr),
    solver(nullptr)
{
    ParametersInputter paramsCreator(FILENAMES.at("parameters"));
    params = paramsCreator.create();

    GlobalScope::getInstance().setParameters(params);
    startBLH = {params->setup.latitude, params->setup.longitude, params->setup.height};
}

Vector Core::calculateEndpoint()
{
    Vector coordinate = blh2ecef(startBLH);
    
    Vector velocity = {0, params->setup.velocity, 0};
    velocity = LinAlg::rotateAbout(velocity, {1,0,0}, params->setup.latitude);
    velocity = LinAlg::rotateAbout(velocity, {0,0,1}, params->setup.longitude - M_PI_2);
    // also need to rotate about coordinate to direct by azimuth in case when velocity isn't colinear with coordinate

    model = new BR3DRoundEarth(params, coordinate, velocity); 
    solver = new RK4Solver(model, 1e-2);

    std::ofstream file("trajectory.txt");
    double step = 2, time = 0;
    auto state = solver->solve(time);
    auto lastState = Vector(state.size());

    while ((state - lastState).norm() > 0.01) {
        file << time << ' ' << state[0] << ' ' << state[1] << ' ' << state[2] << '\n';
        time += step;
        lastState = state;
        try {
            state = solver->solve(time);
        } catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << '\n';
            break;
        }
    }
    file.close();

    // bin search for accurate flight time
    double r_time = time-step, l_time = time - 2*step;
    while (r_time - l_time > 1e-6) {
        
        double mid = (r_time + l_time) / 2;
        state = solver->solve(mid);
        if ((state - lastState).norm() < 0.001) {
            r_time = mid;
        } else {
            l_time = mid;
        }
    }

    flightTime = r_time;
    Vector blhEnd = ecef2blh(solver->solve(flightTime));

    return blhEnd;
}

std::vector<std::pair<double, double>> Core::heights(int points)
{
    std::vector<std::pair<double, double>> result(points);
    Vector start = blh2ecef(startBLH);

    for(int i = 0; i <= points-1; i ++) {
        double t = flightTime / (points-1) * i;
        const auto& state = solver->solve(t);
        Vector h = state - LinAlg::projectionOnEllipse(state, Constants::Earth::MAJOR_AXIS,Constants::Earth::MAJOR_AXIS,Constants::Earth::MINOR_AXIS);
        double height = h.norm();
        double arcLength = LinAlg::angle(state, start) * Constants::Earth::MAJOR_AXIS; // sphere model
        result[i] = {arcLength, height};
    }

    return result;
}

Vector Core::getStartBLH() const
{
    return startBLH;
}

double Core::getFlightTime() const
{
    return flightTime;
}

Core::~Core()
{
    delete params;
    delete solver;
    delete model;
}

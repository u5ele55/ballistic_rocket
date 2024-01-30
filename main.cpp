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

#include "core/Core.hpp"

int main() {
    Core core;

    Vector blhStart = core.getStartBLH();
    auto blhEnd = core.calculateEndpoint();

    std::cout << "Flight time: " << core.getFlightTime() << " s. \n";
    
    blhStart[0] *= 180 / M_PI;
    blhStart[1] *= 180 / M_PI;
    
    blhEnd[0] *= 180 / M_PI;
    blhEnd[1] *= 180 / M_PI;
    std::cout << "Start point: " << blhStart
              << "\nEnd point: " << blhEnd << '\n';

    std::ofstream heights("heights.txt");
    for(auto const& distHeight : core.heights()) {
        heights << distHeight.first << " " << distHeight.second << '\n';
    }
    heights.close();

    std::cout << "\nFinished.\n";

    return 0;
}
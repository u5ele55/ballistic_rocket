#pragma once

#include <cmath>

namespace Constants
{
    namespace Earth
    {
        // ПЗ - 90.11
        const double ANGULAR_SPEED = 7.292115e-5; // rad/sec
        const double MASS = 5.9742e24;
        const double GEOCENTRIC_GRAVITATION_CONSTANT = 398600.4418e9;
        const double MAJOR_AXIS = 6378136; // in meters
        const double MINOR_AXIS = 6356752.3142; // in meters
        const double SECONDS_IN_DAY = 86400;
    } // namespace Earth
    namespace Common
    {
        const double G = 6.67430e-11;
    } // namespace Common
    
} // namespace Constants
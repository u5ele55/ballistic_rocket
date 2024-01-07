#include "GlobalScope.hpp"
#include "../utils/function/physics/AirDensityExponentialModel.hpp"

GlobalScope::GlobalScope() 
    : soundSpeed(nullptr),
    power(nullptr),
    airDensity(nullptr),
    mass(nullptr),
    pitchAngle(nullptr)
{}

GlobalScope& GlobalScope::getInstance()
{
    static GlobalScope instance;
    return instance;
}

Function<double, double> &GlobalScope::getSoundSpeedEvaluator()
{
    if (soundSpeed == nullptr) {
        // create soundSpeed
    }

    return *soundSpeed;
}

Function<double, double> &GlobalScope::getPowerEvaluator()
{
    if (power == nullptr) {
        power = creator.createLinearInterpolator(FILENAMES.at("power"));
    }

    return *power;
}

Function<double, double> &GlobalScope::getMassEvaluator()
{
    if (mass == nullptr) {
        mass = creator.createLinearInterpolator(FILENAMES.at("mass"));
    }

    return *mass;
}

Function<double, double> &GlobalScope::getPitchAngleEvaluator()
{
    if (pitchAngle == nullptr) {
        pitchAngle = creator.createLinearInterpolator(FILENAMES.at("pitch_angle"));
    }

    return *pitchAngle;
}

Function<double, double> &GlobalScope::getAirDensityEvaluator()
{
    if (airDensity == nullptr) {
        airDensity = new AirDensityExponentialModel;
    }

    return *airDensity;
}

GlobalScope::~GlobalScope()
{
    delete soundSpeed;
}

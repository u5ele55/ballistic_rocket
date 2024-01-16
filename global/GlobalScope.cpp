#include "GlobalScope.hpp"
#include "../utils/Function/physics/AirDensityExponentialModel.hpp"
#include "../utils/file_input/filenames.hpp"

GlobalScope::GlobalScope() 
    : soundSpeed(nullptr),
    power(nullptr),
    airDensity(nullptr),
    mass(nullptr),
    pitchAngle(nullptr),
    dragCoef1(nullptr),
    dragCoef2(nullptr),
    dragCoefW(nullptr)
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
#include <iostream>
Function<double, Function<double, double> &> &GlobalScope::getDragCoef1Evaluator()
{
    if (dragCoef1 == nullptr) {
        dragCoef1 = reinterpret_cast<Function<double, Function<double, double>&>*>(
            creator.createConditionalLinearInterpolator(FILENAMES.at("Cx_1")));
    }

    return *dragCoef1;
}

Function<double, Function<double, double> &> &GlobalScope::getDragCoef2Evaluator()
{
    if (dragCoef2 == nullptr) {
        dragCoef2 = reinterpret_cast<Function<double, Function<double, double>&>*>(
            creator.createConditionalLinearInterpolator(FILENAMES.at("Cx_2")));
    }

    return *dragCoef2;
}

Function<double, double> &GlobalScope::getDragCoefWarheadEvaluator()
{
    if (dragCoefW == nullptr) {
        dragCoefW = creator.createLinearInterpolator(FILENAMES.at("Cx_warhead"));
    }

    return *dragCoefW;
}

GlobalScope::~GlobalScope()
{
    delete soundSpeed;
    delete airDensity;
    delete pitchAngle;
    delete power;
    delete mass;

    delete dragCoef1;
    delete dragCoef2;
    delete dragCoefW;
}

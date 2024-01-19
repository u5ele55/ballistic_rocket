#include "GlobalScope.hpp"
#include "../utils/Function/physics/AirDensityExponentialModel.hpp"
#include "../utils/file_input/filenames.hpp"

GlobalScope::GlobalScope() 
    : power(nullptr),
    atmosphere(nullptr),
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

Function<double, AtmosphereParameters> &GlobalScope::getAtmosphereParamsEvaluator()
{
    if (atmosphere == nullptr) {
        atmosphere = new StandartAtmosphereParameters;
    }

    return *atmosphere;
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
            creator.createConditionalLinearInterpolator(FILENAMES.at("Cx_2"), true));
    }
    
    return *dragCoef2;
}

Function<double, double> &GlobalScope::getDragCoefWarheadEvaluator()
{
    if (dragCoefW == nullptr) {
        dragCoefW = creator.createLinearInterpolator(FILENAMES.at("Cx_warhead"), true);
    }

    return *dragCoefW;
}

GlobalScope::~GlobalScope()
{
    delete atmosphere;
    delete pitchAngle;
    delete power;
    delete mass;

    delete dragCoef1;
    delete dragCoef2;
    delete dragCoefW;
}

#include "GlobalScope.hpp"
#include "Function/physics/AirDensityExponentialModel.hpp"
#include "file_input/filenames.hpp"

#include <stdexcept>

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
    if (params == nullptr) {
        throw std::runtime_error("Power evaluator can't be created because parameters is not initialized");
    }
    if (power == nullptr) {
        power = creator.createDiscontinuityLinearInterpolator(
            FILENAMES.at("power"), {params->stageEndtime.first, params->stageEndtime.second}
        );
    }

    return *power;
}

Function<double, double> &GlobalScope::getMassEvaluator()
{
    if (params == nullptr) {
        throw std::runtime_error("Mass evaluator can't be created because parameters is not initialized");
    }
    if (mass == nullptr) {
        mass = creator.createDiscontinuityLinearInterpolator(
            FILENAMES.at("mass"), {params->stageEndtime.first, params->stageEndtime.second}
        );
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

void GlobalScope::setParameters(Parameters *params)
{
    this->params = params;
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

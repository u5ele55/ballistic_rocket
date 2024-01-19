#pragma once

#include "../utils/Function/Function.hpp"
#include "../utils/Function/physics/AtmosphereParameters.hpp"
#include "FunctionCreator.hpp"

class GlobalScope {
private:
    GlobalScope();
    FunctionCreator creator;
    
    Function<double, double> *power;
    Function<double, double> *mass;
    Function<double, double> *pitchAngle;
    Function<double, AtmosphereParameters> *atmosphere;

    Function<double, Function<double, double>&> *dragCoef1;
    Function<double, Function<double, double>&> *dragCoef2;
    Function<double, double> *dragCoefW;
public:
    GlobalScope(GlobalScope const&)    = delete;
    void operator=(GlobalScope const&) = delete;
    static GlobalScope& getInstance();
    ~GlobalScope();

    Function<double, AtmosphereParameters>& getAtmosphereParamsEvaluator();
    Function<double, double>& getPowerEvaluator();
    Function<double, double>& getMassEvaluator();
    Function<double, double>& getPitchAngleEvaluator();

    Function<double, Function<double, double>&>& getDragCoef1Evaluator();
    Function<double, Function<double, double>&>& getDragCoef2Evaluator();
    Function<double, double>& getDragCoefWarheadEvaluator();
};
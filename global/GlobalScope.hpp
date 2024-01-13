#pragma once

#include "../utils/Function/Function.hpp"
#include "FunctionCreator.hpp"

class GlobalScope {
private:
    GlobalScope();
    FunctionCreator creator;
    
    Function<double, double> *soundSpeed;
    Function<double, double> *power;
    Function<double, double> *mass;
    Function<double, double> *pitchAngle;
    Function<double, double> *airDensity;
public:
    GlobalScope(GlobalScope const&)    = delete;
    void operator=(GlobalScope const&) = delete;
    static GlobalScope& getInstance();
    ~GlobalScope();

    Function<double, double>& getSoundSpeedEvaluator();
    Function<double, double>& getPowerEvaluator();
    Function<double, double>& getMassEvaluator();
    Function<double, double>& getPitchAngleEvaluator();
    Function<double, double>& getAirDensityEvaluator();
};
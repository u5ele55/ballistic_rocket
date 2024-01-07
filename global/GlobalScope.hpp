#pragma once

#include "../utils/Function/Function.hpp"
#include "FunctionCreator.hpp"

#include <map>

const std::map<std::string, std::string> FILENAMES = {
    {"mass", "../datafiles/mass.txt"},
    {"power", "../datafiles/power.txt"},
    {"pitch_angle", "../datafiles/pitch_angle.txt"}
};

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
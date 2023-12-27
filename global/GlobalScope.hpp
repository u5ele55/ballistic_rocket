#pragma once

#include "../utils/Function/Function.hpp"

class GlobalScope {
private:
    GlobalScope();
public:
    GlobalScope(GlobalScope const&)    = delete;
    void operator=(GlobalScope const&) = delete;
    static GlobalScope& getInstance();
    ~GlobalScope();

private:
    Function<double, double> *soundSpeed;
public:
    Function<double, double>& getSoundSpeedEvaluator();
};
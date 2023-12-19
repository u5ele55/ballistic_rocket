#pragma once

#include "../utils/LinearInterpolatedFunction.hpp"

class GlobalScope {
private:
    GlobalScope();
public:
    GlobalScope(GlobalScope const&)    = delete;
    void operator=(GlobalScope const&) = delete;
    static GlobalScope& getInstance();

private:
    LinearInterpolatedFunction *mach;
public:
    LinearInterpolatedFunction& getMachCalculator();
    ~GlobalScope();
};
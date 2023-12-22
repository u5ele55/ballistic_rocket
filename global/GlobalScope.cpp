#include "GlobalScope.hpp"

GlobalScope::GlobalScope() 
    : soundSpeed(nullptr) 
{

}

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

GlobalScope::~GlobalScope()
{
    delete soundSpeed;
}

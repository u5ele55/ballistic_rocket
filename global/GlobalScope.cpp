#include "GlobalScope.hpp"

GlobalScope::GlobalScope() 
    : mach(nullptr) 
{

}

GlobalScope& GlobalScope::getInstance()
{
    static GlobalScope instance;
    return instance;
}

LinearInterpolatedFunction &GlobalScope::getMachCalculator()
{
    if (mach == nullptr) {
        // create mach
    }

    return *mach;
}

GlobalScope::~GlobalScope()
{
    delete mach;
}

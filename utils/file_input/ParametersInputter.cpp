#include "ParametersInputter.hpp"
#include <cmath>

ParametersInputter::ParametersInputter(const std::string &filename)
    : file(filename) {}

Parameters *ParametersInputter::create()
{
    SetupParameters setup;
    file 
        >> setup.azimuth 
        >> setup.latitude 
        >> setup.longitude
        >> setup.height
        >> setup.velocity;
    setup.azimuth *= M_PI / 180;
    setup.latitude *= M_PI / 180;
    setup.longitude *= M_PI / 180;

    MissileParameters missile;
    file 
        >> missile.nozzleCutoffArea1
        >> missile.midelArea1
        >> missile.nozzleCutoffArea2
        >> missile.midelArea2
        >> missile.nozzleCutoffArea3
        >> missile.midelAreaW;
    
    StageEndtime stageEndtime;
    file 
        >> stageEndtime.first 
        >> stageEndtime.second 
        >> stageEndtime.third;
    
    Parameters *res = new Parameters;
    res->missile = missile;
    res->setup = setup;
    res->stageEndtime = stageEndtime;

    return res;
}

ParametersInputter::~ParametersInputter()
{
    file.close();
}
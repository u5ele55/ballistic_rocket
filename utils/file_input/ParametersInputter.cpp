#include "ParametersInputter.hpp"

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
    
    MissileParameters missile;
    file 
        >> missile.nozzleCutoffArea1
        >> missile.midelArea1
        >> missile.nozzleCutoffArea2
        >> missile.midelArea2
        >> missile.nozzleCutoffArea3;
    
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
#pragma once

struct MissileParameters
{
    double midelArea1;
    double midelArea2;
    double midelAreaW;
    double nozzleCutoffArea1;
    double nozzleCutoffArea2;
    double nozzleCutoffArea3;
};

struct SetupParameters
{
    double azimuth;
    double latitude;
    double longitude;
    double height;
    double velocity;
};

struct StageEndtime 
{
    double first;
    double second;
    double third;
};

struct Parameters
{
    SetupParameters setup;
    MissileParameters missile;
    StageEndtime stageEndtime;
};
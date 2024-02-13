#pragma once
#include "IFileInputter.hpp"
#include "ballistic_rocket/system/Parameters.hpp"

class ParametersInputter : IFileInputter<Parameters>
{
private:
    std::ifstream file;
public:
    ParametersInputter(const std::string& filename);
    Parameters* create();
    ~ParametersInputter();
};
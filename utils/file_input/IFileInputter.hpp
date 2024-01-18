#pragma once
#include <string>
#include <fstream>

template <class T>
class IFileInputter
{
public:
    virtual T* create() = 0;
    virtual ~IFileInputter() {};
};

#pragma once

#include "../../utils/Vector.hpp"

class ISystem
{
public:
    virtual ~ISystem() {};
    
    virtual void f(Vector &state, double time) const = 0;

    virtual Vector getInitialState() const = 0;
};
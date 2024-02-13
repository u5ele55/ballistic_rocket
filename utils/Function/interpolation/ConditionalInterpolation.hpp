#pragma once
#include "Function/Function.hpp"
#include "InterpolatedFunction.hpp"

class ConditionalInterpolation : public Function<double, InterpolatedFunction&> 
{
protected:
    std::vector< std::pair<double, InterpolatedFunction*> > use;
public:
    virtual InterpolatedFunction& operator()(double h) = 0;
    virtual ~ConditionalInterpolation() {
        for (auto& u : use)
            delete u.second;
    }
};
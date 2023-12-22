#pragma once

template <class Input, class Output>
class Function
{
public:
    virtual Output operator()(Input t) = 0;
};
#pragma once

#include "Vector.hpp"

class LinAlg {
public:
    static Vector rotateAbout(const Vector& src, const Vector& axis, double angle);
};
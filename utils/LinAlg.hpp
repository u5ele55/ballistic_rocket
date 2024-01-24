#pragma once

#include "Vector.hpp"

class LinAlg {
public:
    static Vector rotateAbout(const Vector& src, const Vector& axis, double angle);
    static double angle(const Vector& a, const Vector& b);
    static Vector projectionOnPlane(const Vector& src, const Vector& basis1, const Vector& basis2);

    static Vector projectionOnEllipse(const Vector& r, double a, double b, double c);
};
#include "LinAlg.hpp"

#include <cmath>

// method from https://math.stackexchange.com/questions/511370/how-to-rotate-one-vector-about-another
Vector LinAlg::rotateAbout(const Vector &a, const Vector &b, double angle)
{
    Vector a_prl_b = b * ( a.dot(b) / b.dot(b) );
    Vector a_ort_b = a - a_prl_b;

    Vector w = b.cross(a_ort_b);

    double x1 = cos(angle) / a_ort_b.norm();
    double x2 = sin(angle) / w.norm();

    Vector a_ort_rot_b = (a_ort_b * x1 + w * x2) * a_ort_b.norm();

    Vector a_rot_b = a_ort_rot_b + a_prl_b;

    return a_rot_b;
}
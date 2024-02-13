#include "LinAlg.hpp"

#include <cmath>

#include <iostream>
// method from https://math.stackexchange.com/questions/511370/how-to-rotate-one-vector-about-another
Vector LinAlg::rotateAbout(const Vector &a, const Vector &b, double angle)
{
    Vector a_prl_b = b * ( a.dot(b) / b.dot(b) );
    Vector a_ort_b = a - a_prl_b;
    if (a_ort_b.norm() == 0) {
        return a;
    }
    Vector w = b.cross(a_ort_b);

    double x1 = cos(angle) / a_ort_b.norm();
    double x2 = sin(angle) / w.norm();

    Vector a_ort_rot_b = (a_ort_b * x1 + w * x2) * a_ort_b.norm();

    Vector a_rot_b = a_ort_rot_b + a_prl_b;

    return a_rot_b;
}

double LinAlg::angle(const Vector &a, const Vector &b)
{
    double normA = a.norm(), normB = b.norm();

    if (normA == 0 || normB == 0) {
        return 0;
    }

    double cos_angle = a.dot(b) / (normA * normB);

    return acos(cos_angle);
}

Vector LinAlg::projectionOnPlane(const Vector &src, const Vector &basis1, const Vector &basis2)
{
    Vector n = basis1.cross(basis2); // normal vector

    return projectionOnPlane(src, n);
}

Vector LinAlg::projectionOnPlane(const Vector &src, const Vector &normal)
{
    Vector n = normal / normal.norm();
    Vector proj = n * src.dot(n);

    return proj;
}

Vector LinAlg::projectionOnEllipse(const Vector &r, double a, double b, double c)
{
    double X = r[0], Y = r[1], Z = r[2];
    double t = 1 / sqrt(X*X / (a*a) + Y*Y / (b*b) + Z*Z / (c*c));

    return r * t;
}

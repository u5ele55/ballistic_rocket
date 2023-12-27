#include <iostream>
#include "utils/Vector.hpp"
#include "utils/function/interpolation/LinearInterpolatedFunction.hpp"
#include "utils/function/interpolation/CubicSplinesInterpolation.hpp"
#include <vector>


int main() {
    // Interpolation test
    std::vector<double> x = {2, 5, 8, 9, 12, 15, 20, 22, 25};
    std::vector<double> y = {3, -1, 6, 8, 3, 6, 13, 0, 3};

    CatmullRomSplineInterpolation fun(x, y);

    std::cout << x.size() << '\n';
    for(int i = 0; i < x.size(); i ++) {
        std::cout << x[i] << ' ' << y[i] << '\n';
    }

    double step = 0.2;
    int N = (x[x.size() - 1] - x[0]) / step;
    std::cout << N << '\n';
    for (int i = 0; i < N; i ++) {
        double X = x[0] + step * i;
        std::cout << X << ' ' << fun(X) << '\n';
    }

    return 0;
}
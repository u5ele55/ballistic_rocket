#include "CubicSplinesInterpolation.hpp"

#include <stdexcept>

CubicSplinesInterpolation::CubicSplinesInterpolation(std::vector<double> x, std::vector<double> y, std::vector<Vector> coefs)
    : InterpolatedFunction(x, y), coefs(coefs), y_near(4), a(4)
{
    if (coefs.size() != 4) {
        throw std::runtime_error("Size of coefs vector must be 4 x 4");
    }

    // continue grid to the left and to the right so splines win't break for 
    // first and last segments
    double x_1 = 2 * x[0] - x[1];
    double y_1 = 2 * y[0] - y[1];
    grid.emplace(grid.begin(), x_1, y_1);

    int n = x.size();
    double x_n = 2 * x[n-1] - x[n-2];
    double y_n = 2 * y[n-1] - y[n-2];
    grid.emplace_back(x_n, y_n);

    gridSize += 2;
}

double CubicSplinesInterpolation::operator()(double t)
{
    // bin search for x[i] < t < x[i+1]
    if (t < grid[1].first || t > grid[gridSize - 2].first) {
        throw std::runtime_error("t is out of range of interpolation");
    }
    int l = 1, r = gridSize-1, mid;

    while (r - l > 1) {
        mid = (r+l) / 2;
        if (grid[mid].first < t) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    double x1 = grid[l].first, x2 = grid[r].first;
    double y1 = grid[l].second, y2 = grid[r].second;
    
    for (int i = 0; i < 4; i ++) {
        y_near[i] = grid[l-1 + i].second;
    }

    double mu = (t - x1) / (x2 - x1);
    double mu2 = mu*mu;

    // std::cout << "a: ";
    for(int i = 0; i < 4; i ++) {
        a[i] = 0; 
        for (int j = 0; j < 4; j ++) {
            a[i] += y_near[j] * coefs[i][j];
            // std::cout << y_near[i] << '*' << coefs[i][j] << ' ';
        }
        // std::cout << '=' << a[i] << ' ';
    }
    // std::cout << '\n';

    return a[0]*mu*mu2 + a[1]*mu2 + a[2]*mu + a[3];
}

#include <iostream>
#include "utils/Vector.hpp"
#include "utils/LinearInterpolatedFunction.hpp"

int main() {
    Vector test(3);
    test[2] = 54;

    LinearInterpolatedFunction fun({2, 4, 6}, {10, 0, 20});

    std::cout << fun(5.9);

    return 0;
}
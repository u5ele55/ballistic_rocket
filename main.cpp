#include <iostream>
#include "utils/Vector.hpp"

int main() {
    Vector test(3);
    test[2] = 54;

    std::cout << test;

    return 0;
}
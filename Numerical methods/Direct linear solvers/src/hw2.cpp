#include <iostream>
#include <iomanip>

#include "Utils.h"
#include "Matrix.h"
#include "MatrixUtils.h"

int main()
{
    DLSES::Matrix<double> mat(3, 3);
    mat(0, 0) = 3;
    mat(0, 1) = 7;
    mat(0, 2) = mat(1, 2) = mat(2, 0) = 1;
    mat(1, 0) = mat(2, 1) = 2;
    mat(2, 2) = 6;

    print(mat);
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(6); //specify precision

    auto inv = DLSES::inverse(mat);
    std::cout << "Inverse" << std::endl;
    print(inv);
    std::cout << std::endl;

    std::cout << "Check" << std::endl;
    print(inv * mat);
    std::cout << std::endl;

    auto det = DLSES::det(mat);
    std::cout << "Det: " << det << std::endl;

    return 0;
}

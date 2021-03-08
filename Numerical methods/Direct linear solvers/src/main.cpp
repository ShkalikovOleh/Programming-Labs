#include <iostream>
#include <iomanip>

#include "Matrix.h"
#include "Vector.h"
#include "Solvers.h"
#include "Utils.h"

int main()
{
    DLSES::Matrix<double> mat(4, 4);
    mat(0, 0) = mat(0, 3) = mat(3, 0) = 5.5;
    mat(0, 1) = mat(1, 0) = mat(3, 1) = mat(1, 3) = 7.0;
    mat(1, 1) = mat(2, 2) = mat(3,3) = 10.5;
    mat(1, 2) = mat(2, 1) = 8.0;
    mat(2, 0) = mat(0,2) = 6.0;
    mat(3, 2) = mat(2,3) = 9.0;

    std::cout << "Matrix A" << std::endl;
    print(mat);
    std::cout << std::endl;

    DLSES::Vector<int> vec(4);
    vec(0) = 23;
    vec(1) = 32;
    vec(2) = 33;
    vec(3) = 31;

    std::cout << "Vector b" << std::endl;
    print(vec);
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(6); //specify precision

    auto xch = DLSES::choleskySolve(mat, vec);
    std::cout << "Roots cholesky" << std::endl;
    print(xch);
    std::cout << std::endl;

    auto xld = DLSES::ldlSolve(mat, vec);
    std::cout << "Roots LDL" << std::endl;
    print(xld);
    std::cout << std::endl;

    auto xgj = DLSES::gaussJordanSolve(mat, vec);
    std::cout << "Gauss-Jordan" << std::endl;
    print(xgj);
    std::cout << std::endl;

    DLSES::Vector<double> res = mat * xld - vec;
    std::cout << "A*x - b" << std::endl;
    print(res);

    return 0;
}
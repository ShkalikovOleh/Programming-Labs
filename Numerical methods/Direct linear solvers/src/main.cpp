#include <iostream>

#include "Matrix.h"
#include "Vector.h"
#include "Solvers.h"

template <typename T>
void print_matrix(const DLSES::Matrix<T> &matrix)
{
    for (size_t i = 0; i < matrix.nrow(); i++)
    {
        for (size_t j = 0; j < matrix.ncol(); j++)
        {
            std::cout << matrix(i, j) << "\t";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void print_vector(const DLSES::Vector<T> &vector)
{
    for (size_t i = 0; i < vector.nval(); i++)
    {
        std::cout << vector(i) << "\t";
    }
    std::cout << std::endl;
}

int main()
{
    DLSES::Matrix<double> mat(4, 4);
    mat(0, 0) = mat(0, 3) = mat(3, 0) = 5.5;
    mat(0, 1) = mat(1, 0) = mat(3, 1) = mat(1, 3) = 7.0;
    mat(1, 1) = mat(2, 2) = mat(3,3) = 10.5;
    mat(1, 2) = mat(2, 1) = 8.0;
    mat(2, 0) = mat(0,2) = 6.0;
    mat(3, 2) = mat(2,3) = 9.0;

    //print_matrix(mat);

    DLSES::Vector<double> vec(4);
    vec(0) = 23;
    vec(1) = 32;
    vec(2) = 33;
    vec(3) = 31;

    auto x = choleckySolve(mat, vec);
    std::cout << "Roots" << std::endl;
    print_vector(x);

    DLSES::Vector<double> res = mat * x;
    std::cout << "Check" << std::endl;
    print_vector(res);

    return 0;
}
#pragma once

#include <cmath>

#include "Matrix.h"
#include "Vector.h"

namespace DLSES
{
#ifndef LATEX
    template <typename T>
    void print(const Matrix<T> &matrix)
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
    void print(const Vector<T> &vector)
    {
        for (size_t i = 0; i < vector.nval(); i++)
        {
            std::cout << vector(i) << "\t";
        }
        std::cout << std::endl;
    }

    template <typename T>
    void printAbs(const Vector<T> &vector)
    {
        for (size_t i = 0; i < vector.nval(); i++)
        {
            std::cout << std::abs(vector(i)) << "\t";
        }
        std::cout << std::endl;
    }
#else
    template <typename T>
    void print(const Matrix<T> &matrix)
    {
        std::cout << "\\begin{pmatrix}" << std::endl;
        for (size_t i = 0; i < matrix.nrow(); i++)
        {
            std::cout << "\t";
            for (size_t j = 0; j < matrix.ncol() - 1; j++)
            {
                std::cout << matrix(i, j) << " & ";
            }
            std::cout << matrix(i, matrix.ncol() - 1);
            if (i != matrix.nrow() - 1)
                std::cout << " \\\\";
            std::cout << std::endl;
        }
        std::cout << "\\end{pmatrix}" << std::endl;
    }

    template <typename T>
    void print(const Vector<T> &vector)
    {
        std::cout << "\\begin{pmatrix}" << std::endl << "\t";;
        for (size_t i = 0; i < vector.nval() - 1; i++)
        {
            std::cout << vector(i) << " \\\\ ";
        }
        std::cout << vector(vector.nval() - 1) << std::endl << "\\end{pmatrix}";
    }

    template <typename T>
    void printAbs(const Vector<T> &vector)
    {
        std::cout << "\\begin{pmatrix}" << std::endl << "\t";;
        for (size_t i = 0; i < vector.nval() - 1; i++)
        {
            std::cout << std::abs(vector(i)) << " \\\\ ";
        }
        std::cout << vector(vector.nval() - 1) << std::endl << "\\end{pmatrix}";
    }
#endif
}

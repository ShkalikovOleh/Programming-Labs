#pragma once

#include "Buffer.h"
#include "Vector.h"

namespace DLSES
{
    template <typename T>
    class Matrix
    {
    public:
        Matrix(size_t nrow, size_t ncol);

        size_t nrow() const noexcept { return _nrow; }
        size_t ncol() const noexcept { return _ncol; }

        T& operator()(size_t i, size_t j);
        const T& operator()(size_t i, size_t j) const;

        Matrix transpose() const;
        bool isSymmetric() const noexcept;

    private:
        size_t _nrow;
        size_t _ncol;
        Buffer<T> _buff;
    };

    template <typename T>
    Matrix<T>::Matrix(size_t nrow, size_t ncol) : _buff(nrow * ncol), _nrow(nrow), _ncol(ncol) {}

    template <typename T>
    T& Matrix<T>::operator()(size_t i, size_t j)
    {
        if (i >= _nrow || j >= _ncol)
            throw std::invalid_argument("Position is out of range");
        return _buff[i * _ncol + j];
    }

    template <typename T>
    const T& Matrix<T>::operator()(size_t i, size_t j) const
    {
        if (i >= _nrow || j >= _ncol)
            throw std::invalid_argument("Position is out of range");
        return _buff[i * _ncol + j];
    }

    template <typename T>
    Matrix<T> Matrix<T>::transpose() const
    {
        Matrix<T> result(_nrow, _ncol);

        for (size_t i = 0; i < _nrow; i++)
        {
            for (size_t j = 0; j < _ncol; j++)
            {
                result(i, j) = operator()(j, i);
            }
        }

        return result;
    }

    template <typename T>
    bool Matrix<T>::isSymmetric() const noexcept
    {
        for (size_t i = 0; i < _nrow; i++)
        {
            for (size_t j = 0; j < i; j++)
            {
                if (operator()(i, j) != operator()(j, i))
                    return false;

            }
        }
        return true;
    }

    template <typename T>
    Matrix<T> operator*(const DLSES::Matrix<T> &rhs, const DLSES::Matrix<T> &lhs)
    {
        if (rhs.ncol() != lhs.nrow())
            throw std::invalid_argument("Number of column != number of row");

        Matrix<T> result(rhs.nrow(), lhs.ncol());

        for (size_t i = 0; i < rhs.nrow(); i++)
        {
            for (size_t j = 0; j < lhs.ncol(); j++)
            {
                for (size_t k = 0; k < rhs.ncol(); k++)
                {
                    result(i, j) += rhs(i, k) * lhs(k, j);
                }
            }
        }

        return result;
    }

    template <typename T>
    Vector<T> operator*(const Matrix<T> &matrix, const Vector<T> &vector)
    {
        if (matrix.ncol() != vector.nval())
            throw std::invalid_argument("Number of column != size of vector");

        Vector<T> result(matrix.nrow());

        for (size_t i = 0; i < matrix.nrow(); i++)
        {
            for (size_t j = 0; j < matrix.ncol(); j++)
            {
                result(i) += vector(j) * matrix(i, j);
            }
        }

        return result;
    }
}

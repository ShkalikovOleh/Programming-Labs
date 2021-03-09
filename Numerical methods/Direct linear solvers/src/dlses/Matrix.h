#pragma once

#include "Buffer.h"
#include "Vector.h"

namespace DLSES
{
    template <typename T>
    class IMatrix
    {
    public:
        size_t nrow() const noexcept { return _nrow; }
        size_t ncol() const noexcept { return _ncol; }

        virtual T &operator()(size_t i, size_t j) = 0;
        virtual const T& operator()(size_t i, size_t j) const = 0;

    protected:
        size_t _nrow;
        size_t _ncol;
    };

    template <typename T>
    class TransposeView : public IMatrix<T>
    {
    public:
        TransposeView(IMatrix<T> &matrix)
        {
            _matrix = &matrix;
            this->_nrow = matrix.nrow();
            this->_ncol = matrix.ncol();
        }

        T &operator()(size_t i, size_t j) override
        {
            if (j >= this->_nrow || i >= this->_ncol)
                throw std::invalid_argument("Position is out of range");
            return _matrix->operator()(j, i);
        }

        const T& operator()(size_t i, size_t j) const override
        {
            if (j >= this->_nrow || i >= this->_ncol)
                throw std::invalid_argument("Position is out of range");
            return _matrix->operator()(j, i);
        }


    private:
        IMatrix<T>* _matrix;
    };

    template <typename T>
    class Matrix : public IMatrix<T>
    {
    public:
        Matrix(size_t nrow, size_t ncol) : _buff(nrow * ncol)
        {
            this->_nrow = nrow;
            this->_ncol = ncol;
        }

        template<typename U>
        Matrix(const Matrix<U>& matrix) : _buff(matrix._buff.size())
        {
            for (size_t i = 0; i < matrix.nrow(); i++)
            {
                for (size_t j = 0; j < matrix.ncol(); j++)
                {
                    _buff[i] = matrix(i, j);
                }
            }
        };

        T &operator()(size_t i, size_t j) override
        {
            if (i >= this->_nrow || j >= this->_ncol)
                throw std::invalid_argument("Position is out of range");
            return _buff[i * this->_ncol + j];
        }

        const T& operator()(size_t i, size_t j) const override
        {
            if (i >= this->_nrow || j >= this->_ncol)
                throw std::invalid_argument("Position is out of range");
            return _buff[i * this->_ncol + j];
        }

        Matrix<T> transpose()
        {
            Matrix<T> result(this->_nrow, this->_ncol);

            for (size_t i = 0; i < this->_nrow; i++)
            {
                for (size_t j = 0; j < this->_ncol; j++)
                {
                    result(i, j) = operator()(j, i);
                }
            }

            return result;
        }

        bool isSymmetric() const noexcept
        {
            if (this->_ncol != this->_nrow)
            return false;

            for (size_t i = 0; i < this->_nrow; i++)
            {
                for (size_t j = 0; j < i; j++)
                {
                    if (operator()(i, j) != operator()(j, i))
                        return false;
                }
            }

            return true;
        }

    private:
        Buffer<T> _buff;
    };

    template <typename T, typename U>
    auto operator*(const IMatrix<T> &rhs, const IMatrix<U> &lhs)
    {
        if (rhs.ncol() != lhs.nrow())
            throw std::invalid_argument("Number of column != number of row");

        Matrix<typename std::common_type<T, U>::type> result(rhs.nrow(), lhs.ncol());

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

    template <typename T, typename U>
    auto operator*(const IMatrix<T> &matrix, const Vector<U> &vector)
    {
        if (matrix.ncol() != vector.nval())
            throw std::invalid_argument("Number of column != size of vector");

        Vector<typename std::common_type<T, U>::type> result(matrix.nrow());

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

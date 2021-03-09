#pragma once

#include <unordered_map>

#include "Vector.h"
#include "Matrix.h"

namespace DLSES
{
    template<typename T>
    class IMatrixView : public IMatrix<T>
    {
    public:
        void swapRows(size_t i, size_t j)
        {
            auto it = _rowMap.find(j);
            if (it != _rowMap.end())
            {
                _rowMap.insert({j, it->second});
            }
            else
            {
                _rowMap.insert({j, i});
            }
            _rowMap.insert({i, j});
        }

        size_t getRow(size_t i) const noexcept
        {
            auto it = _rowMap.find(i);
            if (it != _rowMap.end())
            {
                i = it->second;
            }
            return i;
        };

    protected:
        std::unordered_map<size_t, size_t> _rowMap;
    };

    template<typename T>
    class MatrixView : public IMatrixView<T>
    {
    public:
        MatrixView(IMatrix<T> &matrix)
        {
            _matrix = &matrix;
            this->_nrow = matrix.nrow();
            this->_ncol = matrix.ncol();
        }

        const T& operator()(size_t i, size_t j) const override
        {
            return _matrix->operator()(this->getRow(i), j);
        }

        T& operator()(size_t i, size_t j) override
        {
            return _matrix->operator()(this->getRow(i), j);
        }

    private:
        IMatrix<T>* _matrix;
    };

    template<typename T>
    class MatrixMatrixView : public IMatrixView<T>
    {
    public:
        MatrixMatrixView(IMatrix<T> &matrix1, IMatrix<T> &matrix2)
        {
            _matrix1 = &matrix1;
            _matrix2 = &matrix2;
            this->_nrow = matrix1.nrow();
            this->_ncol = matrix1.ncol() + matrix2.ncol();
        }

        const T& operator()(size_t i, size_t j) const override
        {
            if (j >= this->_ncol)
                throw std::invalid_argument("Position is out of range");

            if (j >= _matrix1->ncol())
            {
                return _matrix2->operator()(this->getRow(i), j - _matrix1->ncol());
            }

            return _matrix1->operator()(i, j);
        }

        T& operator()(size_t i, size_t j) override
        {
            if (j >= this->_ncol)
                throw std::invalid_argument("Position is out of range");

            if (j >= _matrix1->ncol())
            {
                return _matrix2->operator()(this->getRow(i), j - _matrix1->ncol());
            }

            return _matrix1->operator()(i, j);
        }

    private:
        IMatrix<T>* _matrix1;
        IMatrix<T>* _matrix2;
    };

    template<typename T>
    class MatrixVectorView : public IMatrixView<T>
    {
    public:
        MatrixVectorView(IMatrix<T> &matrix, Vector<T> &vector)
        {
            _matrix = &matrix;
            _vector = &vector;
            this->_nrow = matrix.nrow();
            this->_ncol = matrix.ncol() + 1;
        }

        const T& operator()(size_t i, size_t j) const override
        {
            if (j >= this->_ncol)
                throw std::invalid_argument("Position is out of range");

            i = this->getRow(i);
            if (j >= _matrix->ncol())
            {
                return _vector->operator()(i);
            }

            return _matrix->operator()(i, j);
        }

        T& operator()(size_t i, size_t j) override
        {
            if (j >= this->_ncol)
                throw std::invalid_argument("Position is out of range");

            i = this->getRow(i);
            if (j >= _matrix->ncol())
            {
                return _vector->operator()(i);
            }

            return _matrix->operator()(i, j);
        }

    private:
        IMatrix<T>* _matrix;
        Vector<T>* _vector;
    };
}
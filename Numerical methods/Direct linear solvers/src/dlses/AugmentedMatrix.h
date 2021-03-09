#pragma once

#include <unordered_map>

#include "Vector.h"
#include "Matrix.h"

namespace DLSES
{
    template <typename T>
    class AugmentedMatrix
    {
    public:
        AugmentedMatrix(Matrix<T>& mat)
        {
            _type = AugType::None;
            _matrix = &mat;
        }

        AugmentedMatrix(Matrix<T>& mat1, Matrix<T>& mat2)
        {
            if (mat1.nrow() != mat2.nrow())
                throw std::invalid_argument("Different shapes");

            _type = AugType::MatrixAug;
            _augm = &mat2;
            _matrix = &mat1;
        }

        AugmentedMatrix(Matrix<T>& mat, Vector<T>& vec)
        {
            if (mat.nrow() != vec.nval())
                throw std::invalid_argument("Different shapes");

            _type = AugType::VectorAug;
            _augm = &vec;
            _matrix = &mat;
        }

        const T& operator()(size_t i, size_t j) const
        {
            if (j >= ncol())
                throw std::invalid_argument("Position is out of range");

            auto it =_rowPermutation.find(i);
            if (it != _rowPermutation.end())
            {
                i = it->second;
            }

            if (j >= _matrix->ncol())
            {
                switch (_type)
                {
                case AugType::MatrixAug:
                    return (reinterpret_cast<Matrix<T>*>(_augm))->operator()(i, j - _matrix->ncol());
                case AugType::VectorAug:
                    return (reinterpret_cast<Vector<T>*>(_augm))->operator()(i);
                default:
                    throw std::invalid_argument("Position is out of range");
                }
            }

            return _matrix->operator()(i, j);
        }

        T& operator()(size_t i, size_t j)
        {
            if (j >= ncol())
                throw std::invalid_argument("Position is out of range");

            auto it =_rowPermutation.find(i);
            if (it != _rowPermutation.end())
            {
                i = it->second;
            }

            if (j >= _matrix->ncol())
            {
                switch (_type)
                {
                case AugType::MatrixAug:
                    return (reinterpret_cast<Matrix<T>*>(_augm))->operator()(i, j-_matrix->ncol());
                case AugType::VectorAug:
                    return (reinterpret_cast<Vector<T>*>(_augm))->operator()(i);
                default:
                    throw std::invalid_argument("Position is out of range");
                }
            }

            return _matrix->operator()(i, j);
        }

        size_t nrow() const noexcept { return _matrix->nrow(); }

        size_t ncol() const noexcept
        {
            auto ncol = _matrix->nrow();
            switch (_type)
            {
            case AugType::MatrixAug:
                ncol += (reinterpret_cast<Matrix<T>*>(_augm))->ncol();
                break;
            case AugType::VectorAug:
                ncol++;
            default:
                break;
            }

            return ncol;
        }

        void swapRow(size_t i, size_t j)
        {
            _rowPermutation.insert(std::make_pair(i, j));
            _rowPermutation.insert(std::make_pair(j, i));
        }

    private:
        enum AugType
        {
            None,
            MatrixAug,
            VectorAug
        } _type;

        std::unordered_map<size_t, size_t> _rowPermutation;
        void* _augm;
        Matrix<T>* _matrix;
    };
}
#pragma once

#include <cmath>
#include "Buffer.h"

namespace DLSES
{
    template <typename T>
    class Vector
    {
    public:
        Vector(size_t nval) : _buff(nval) {}

        template<typename U>
        Vector(const Vector<U>& vector) : _buff(vector.nval())
        {
            for (size_t i = 0; i < vector.nval(); i++)
            {
                _buff[i] = vector(i);
            }
        };

        inline size_t nval() const noexcept { return _buff.size(); }

        T& operator()(size_t i);
        const T& operator()(size_t i) const;

        auto norm() const noexcept;

    private:
        Buffer<T> _buff;
    };

    template <typename T>
    T& Vector<T>::operator()(size_t i)
    {
        if (i >= _buff.size())
            throw std::invalid_argument("Position is out of range");
        return _buff[i];
    }

    template <typename T>
    const T& Vector<T>::operator()(size_t i) const
    {
        if (i >= _buff.size())
            throw std::invalid_argument("Position is out of range");
        return _buff[i];
    }

    template <typename T>
    auto Vector<T>::norm() const noexcept
    {
        T sum = 0;
        for (size_t i = 0; i < _buff.size(); i++)
        {
            sum += _buff[i] * _buff[i];
        }
        return std::sqrt(sum);
    }

    template <typename T, typename U>
    auto operator+(const Vector<T> &rhs, const Vector<U> &lhs)
    {
        if (rhs.nval() != lhs.nval())
            throw std::invalid_argument("Different size");

        Vector<typename std::common_type<T, U>::type> result(rhs.nval());
        for (size_t i = 0; i < rhs.nval(); i++)
        {
            result(i) = rhs(i) + lhs(i);
        }
        return result;
    }

    template <typename T, typename U>
    auto operator-(const Vector<T> &rhs, const Vector<U> &lhs)
    {
        if (rhs.nval() != lhs.nval())
            throw std::invalid_argument("Different size");

        Vector<typename std::common_type<T, U>::type> result(rhs.nval());
        for (size_t i = 0; i < rhs.nval(); i++)
        {
            result(i) = rhs(i) - lhs(i);
        }
        return result;
    }
}

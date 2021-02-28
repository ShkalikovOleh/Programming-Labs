#pragma once

#include "Buffer.h"

namespace DLSES
{
    template <typename T>
    class Vector
    {
    public:
        Vector(size_t nval) : _buff(nval) {}

        inline size_t nval() const noexcept { return _buff.size(); }

        T& operator()(size_t i);
        const T& operator()(size_t i) const;

        Vector reverse() const;

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
    Vector<T> Vector<T>::reverse() const
    {
        auto size = _buff.size();
        Vector<T> result(size);

        for (size_t i = 0; i < size; i++)
        {
            result(size - i -1) = _buff[i];
        }

        return result;
    }

    template <typename T>
    Vector<T> operator+(const Vector<T> &rhs, const Vector<T> &lhs)
    {
        if (rhs.nval() != lhs.nval())
            throw std::invalid_argument("Different size");

        Vector<T> result(rhs.nval());
        for (size_t i = 0; i < rhs.nval(); i++)
        {
            result(i) = rhs(i) + lhs(i);
        }
        return result;
    }

    template <typename T>
    Vector<T> operator-(const Vector<T> &rhs, const Vector<T> &lhs)
    {
        if (rhs.nval() != lhs.nval())
            throw std::invalid_argument("Different size");

        Vector<T> result(rhs.nval());
        for (size_t i = 0; i < rhs.nval(); i++)
        {
            result(i) = rhs(i) - lhs(i);
        }
        return result;
    }
}

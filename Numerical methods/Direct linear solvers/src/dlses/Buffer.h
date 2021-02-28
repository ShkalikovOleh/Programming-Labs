#pragma once

#include <cstddef>
#include <algorithm>

using std::size_t;


namespace DLSES
{
    template <typename T>
    class Buffer
    {
    public:
        Buffer(size_t size)
        {
            _size = size;
            _data = new T[size]();
        }

        Buffer(const Buffer &lhs)
        {
            _data = new T[lhs._size];
            _size = lhs._size;
            std::copy(lhs._data, lhs._data + lhs._size, _data);
        }

        Buffer(Buffer &&lhs) noexcept
        {
            _data = std::exchange(lhs._data, nullptr);
            _size = std::exchange(lhs._size, 0);
        }

        ~Buffer()
        {
            delete[] _data;
        }

        Buffer& operator=(const Buffer &lhs)
        {
            T *_newData = new T[lhs._size];
            std::copy(lhs._data, lhs._data + lhs._size, _newData);

            _size = lhs._size;
            delete[] _data;
            _data = _newData;

            return *this;
        }

        Buffer& operator=(Buffer &&lhs) noexcept
        {
            std::swap(_data, lhs._data);
            std::swap(_size, lhs._size);
            return *this;
        }

        T& operator[](std::size_t pos)
        {
            return _data[pos];
        }

        const T& operator[](std::size_t pos) const
        {
            return _data[pos];
        }

        inline size_t size() const noexcept { return _size; }

    private:
        T *_data;
        size_t _size;
    };
}

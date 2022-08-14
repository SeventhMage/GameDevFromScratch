#ifndef _Vector4_HPP_
#define _Vector4_HPP_

#include <cmath>
#include <iostream>
#include <cassert>

#include "Math.hpp"
#include "Foundation/Utils/Utils.hpp"

namespace Magic
{
    using namespace std;

    template <typename T>
    class Vector4
    {
    public:
        Vector4();
        Vector4(T x, T y, T z, T w);
        Vector4(T v[4]);

        T Length() const;

        inline float getInvDistanceFrom(const Vector4<T> &other) const
        {
            return Utils::InvSqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z));				
        }

        template <typename T1>
        friend ostream &operator<<(ostream &out, const Vector4<T1> &v);

        union
        {
            struct
            {
                T x, y, z, w;
            };
            T v[4];
        };
    };

    template <typename T>
    Vector4<T>::Vector4()
        : x(0), y(0), z(0)
    {
    }

    template <typename T>
    Vector4<T>::Vector4(T x, T y, T z, T w)
        : x(x), y(y), z(z), w(w)
    {
    }

    template <typename T>
    Vector4<T>::Vector4(T v[4])
    {
        memcpy(this->v, v, sizeof(this->v));
    }

    template <typename T>
    T Vector4<T>::Length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    template <typename T>
    ostream &operator<<(ostream &out, const Vector4<T> &v)
    {
        out << v.x << "," << v.y << "," << v.z << "," << v.w;
        return out;
    }

    typedef Vector4<float> Vector4f;
    typedef Vector4<double> Vector4d;
}
#endif
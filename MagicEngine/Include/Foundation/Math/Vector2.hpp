#ifndef _VECTOR2_HPP_
#define _VECTOR2_HPP_

#include <cmath>
#include <iostream>
#include <cassert>

#include "Math.hpp"
#include "Foundation/Utils/Utils.hpp"

namespace Magic
{
    using namespace std;

    template <typename T>
    class Vector2
    {
    public:
        Vector2();
        Vector2(T x, T y);
        Vector2(T v[2]);
        T Length() const;
        T InvLength() const;
        T SqrLength() const;
        Vector2<T> &Normalize();
        T DotProduct(const Vector2<T> &v) const;
        Vector2<T> &Rotate(T v);

        Vector2<T> operator+(const Vector2<T> &v) const;
        Vector2<T> operator-(const Vector2<T> &v) const;
        Vector2<T> operator*(const Vector2<T> &v) const;
        Vector2<T> operator*(T s) const;
        Vector2<T> operator/(T s) const;
        const T &operator[](int i) const;
        T &operator[](int i);
        Vector2<T> operator-() const;

        static Vector2<T> Lerp(const Vector2<T> &v0, const Vector2<T> &v1, T t);
        static Vector2<T> Slerp(const Vector2<T> &v0, const Vector2<T> &v1, T t);

        template <typename T1>
        friend Vector2<T1> operator*(T1 s, const Vector2<T1> &v);
        template <typename T1>
        friend ostream &operator<<(ostream &out, const Vector2<T1> &v);

        static const Vector2<T> right;
        static const Vector2<T> up;

        union
        {
            struct
            {
                T x, y;
            };
            T v[2];
        };
    };

    template <typename T>
    const Vector2<T> Vector2<T>::right = Vector2<T>(static_cast<T>(1), 0);
    template <typename T>
    const Vector2<T> Vector2<T>::up = Vector2<T>(0, static_cast<T>(1));

    template <typename T>
    Vector2<T>::Vector2()
        : x(0), y(0)
    {
    }

    template <typename T>
    Vector2<T>::Vector2(T x, T y)
        : x(x), y(y)
    {
    }

    template <typename T>
    Vector2<T>::Vector2(T v[2])
    {
        memcpy(this->v, v, sizeof(this->v));
    }

    template <typename T>
    T Vector2<T>::Length() const
    {
        return sqrt(x * x + y * y);
    }

    template <typename T>
    T Vector2<T>::InvLength() const
    {
        return Utils::InvSqrt(x * x + y * y);
    }

    template <typename T>
    T Vector2<T>::SqrLength() const
    {
        return x * x + y * y;
    }

    template <typename T>
    Vector2<T> &Vector2<T>::Normalize()
    {
        T len = Length();
        if (len > 0)
        {
            T invLen = 1 / len;
            x *= invLen;
            y *= invLen;
        }
        return *this;
    }

    template <typename T>
    T Vector2<T>::DotProduct(const Vector2<T> &v) const
    {
        return x * v.x + y * v.y;
    }

    template <typename T>
    Vector2<T> &Vector2<T>::Rotate(T v)
    {
        T c = static_cast<T>(cos(static_cast<long double>(v)));
        T s = static_cast<T>(sin(static_cast<long double>(v)));
        T tmpx = x * c - y * s;
        T tmpy = x * s + y * c;
        x = tmpx;
        y = tmpy;
        return *this;
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator+(const Vector2<T> &v) const
    {
        return Vector2<T>(x + v.x, y + v.y);
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator-(const Vector2<T> &v) const
    {
        return Vector2<T>(x - v.x, y - v.y);
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator*(const Vector2<T> &v) const
    {
        return Vector2<T>(x * v.x, y * v.y);
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator*(T s) const
    {
        return Vector2<T>(x * s, y * s);
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator/(T s) const
    {
        return Vector2<T>(x / s, y / s);
    }

    template <typename T>
    const T &Vector2<T>::operator[](int i) const
    {
        assert(i >= 0 && i < 2);
        return v[i];
    }

    template <typename T>
    T &Vector2<T>::operator[](int i)
    {
        assert(i >= 0 && i < 2);
        return v[i];
    }

    template <typename T>
    Vector2<T> operator*(T s, const Vector2<T> &v)
    {
        return v * s;
    }

    template <typename T>
    Vector2<T> Vector2<T>::operator-() const
    {
        return Vector2(-x, -y);
    }

    template <typename T>
    Vector2<T> Vector2<T>::Lerp(const Vector2<T> &v0, const Vector2<T> &v1, T t)
    {
        return v0 * ((T)1 - t) + v1 * t;
    }

    template <typename T>
    Vector2<T> Vector2<T>::Slerp(const Vector2<T> &v0, const Vector2<T> &v1, T t)
    {
        t = CLAMP(t, 0, (T)1);
        T dotValue = v0.DotProduct(v1);
        if (FLOAT_EQUAL(dotValue, (T)1))
            return v0;
        T v0Length = v0.Length();
        T v1Length = v1.Length();
        T cosOmega = dotValue / (v0Length * v1Length);
        T sinOmega = 1 - cosOmega * cosOmega;
        T omega = acos(cosOmega);
        T sinOneMinTOmega = sin((1 - t) * omega);
        T sinTOmega = sin(t * omega);

        T k0 = sinOneMinTOmega / sinOmega;
        T k1 = sinTOmega / sinOmega;

        return v0 * k0 + v1 * k1;
    }

    template <typename T>
    ostream &operator<<(ostream &out, const Vector2<T> &v)
    {
        out << v.x << "," << v.y;
        return out;
    }

    typedef Vector2<float> Vector2f;
    typedef Vector2f Point2f;
    typedef Vector2<double> Vector2d;
    typedef Vector2d Point2d;
}
#endif
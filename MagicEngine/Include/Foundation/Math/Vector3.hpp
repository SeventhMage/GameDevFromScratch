#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include <cmath>
#include <iostream>
#include <cstring>
#include <cassert>

#include "Math.hpp"
#include "Matrix3x3.hpp"

namespace Magic
{
    using namespace std;

    template <typename T>
    class Vector3
    {
    public:
        Vector3();
        Vector3(T x, T y, T z);
        Vector3(T v[3]);
        T Length() const;
        T SqrLength() const;
        Vector3<T> &Normalize();
        T DotProduct(const Vector3<T> &v) const;
        Vector3<T> CrossProduct(const Vector3<T> &v) const;
        Vector3<T> &RotateByX(T v);
        Vector3<T> &RotateByY(T v);
        Vector3<T> &RotateByZ(T v);
        Vector3<T> &RotateByAxis(const Vector3<T> &axis, T theta);

        Vector3<T> operator+(const Vector3<T> &v) const;
        Vector3<T> operator-(const Vector3<T> &v) const;
        Vector3<T> operator*(const Vector3<T> &v) const;
        Vector3<T> operator*(T s) const;
        const T &operator[](int i) const;
        T &operator[](int i);
        Vector3<T> operator-() const;

        static Vector3<T> Lerp(const Vector3<T> &v0, const Vector3<T> &v1, T t);
        static Vector3<T> Slerp(const Vector3<T> &v0, const Vector3<T> &v1, T t);

        template <typename T1>
        friend Vector3<T1> operator*(T1 s, const Vector3<T1> &v);
        template <typename T1>
        friend ostream &operator<<(ostream &out, const Vector3<T1> &v);
        template <typename T1>
        friend istream &operator>>(istream &in, Vector3<T1> &v);

        static const Vector3<T> right;
        static const Vector3<T> up;
        static const Vector3<T> forward;

        union
        {
            struct
            {
                T x, y, z;
            };
            T v[3];
        };
    };

    template <typename T>
    const Vector3<T> Vector3<T>::right = Vector3<T>(static_cast<T>(1), 0, 0);
    template <typename T>
    const Vector3<T> Vector3<T>::up = Vector3<T>(0, static_cast<T>(1), 0);
    template <typename T>
    const Vector3<T> Vector3<T>::forward = Vector3<T>(0, 0, static_cast<T>(1));

    template <typename T>
    Vector3<T>::Vector3()
        : x(0), y(0), z(0)
    {
    }

    template <typename T>
    Vector3<T>::Vector3(T x, T y, T z)
        : x(x), y(y), z(z)
    {
    }

    template <typename T>
    Vector3<T>::Vector3(T v[3])
    {
        memcpy(this->v, v, sizeof(this->v));
    }

    template <typename T>
    T Vector3<T>::Length() const
    {
        return sqrt(x * x + y * y + z * z);
    }
    template <typename T>
    T Vector3<T>::SqrLength() const
    {
        return x * x + y * y + z * z;
    }

    template <typename T>
    Vector3<T> &Vector3<T>::Normalize()
    {
        T len = Length();
        if (len > 0)
        {
            T invLen = 1 / len;
            x *= invLen;
            y *= invLen;
            z *= invLen;
        }
        return *this;
    }

    template <typename T>
    T Vector3<T>::DotProduct(const Vector3<T> &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    template <typename T>
    Vector3<T> Vector3<T>::CrossProduct(const Vector3<T> &v) const
    {
        return Vector3<T>(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
    }

    template <typename T>
    Vector3<T> &Vector3<T>::RotateByX(T v)
    {
        T c = static_cast<T>(cos(static_cast<long double>(v)));
        T s = static_cast<T>(sin(static_cast<long double>(v)));
        T tmpy = y * c - z * s;
        T tmpz = y * s + z * c;
        y = tmpy;
        z = tmpz;
        return *this;
    }

    template <typename T>
    Vector3<T> &Vector3<T>::RotateByY(T v)
    {
        T c = static_cast<T>(cos(static_cast<long double>(v)));
        T s = static_cast<T>(sin(static_cast<long double>(v)));
        T tmpx = x * c + z * s;
        T tmpz = -x * s + z * c;
        x = tmpx;
        z = tmpz;
        return *this;
    }

    template <typename T>
    Vector3<T> &Vector3<T>::RotateByZ(T v)
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
    Vector3<T> &Vector3<T>::RotateByAxis(const Vector3<T> &axis, T theta)
    {
        Matrix3x3<T> mRot;
        mRot.MakeRotation(axis, theta);
        *this = mRot * *this;
        return *this;
    }

    template <typename T>
    Vector3<T> Vector3<T>::operator+(const Vector3<T> &v) const
    {
        return Vector3<T>(x + v.x, y + v.y, z + v.z);
    }

    template <typename T>
    Vector3<T> Vector3<T>::operator-(const Vector3<T> &v) const
    {
        return Vector3<T>(x - v.x, y - v.y, z - v.z);
    }

    template <typename T>
    Vector3<T> Vector3<T>::operator*(const Vector3<T> &v) const
    {
        return Vector3<T>(x * v.x, y * v.y, z * v.z);
    }

    template <typename T>
    Vector3<T> Vector3<T>::operator*(T s) const
    {
        return Vector3<T>(x * s, y * s, z * s);
    }

    template <typename T>
    const T &Vector3<T>::operator[](int i) const
    {
        assert(i >= 0 && i < 3);
        return v[i];
    }

    template <typename T>
    T &Vector3<T>::operator[](int i)
    {
        assert(i >= 0 && i < 3);
        return v[i];
    }

    template <typename T>
    Vector3<T> operator*(T s, const Vector3<T> &v)
    {
        return v * s;
    }

    template <typename T>
    Vector3<T> Vector3<T>::operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    template <typename T>
    Vector3<T> Vector3<T>::Lerp(const Vector3<T> &v0, const Vector3<T> &v1, T t)
    {
        return v0 * ((T)1 - t) + v1 * t;
    }

    template <typename T>
    Vector3<T> Vector3<T>::Slerp(const Vector3<T> &v0, const Vector3<T> &v1, T t)
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
    ostream &operator<<(ostream &out, const Vector3<T> &v)
    {
        out << v.x << "," << v.y << "," << v.z;
        return out;
    }

    template <typename T>
    istream &operator>>(istream &in, Vector3<T> &v)
    {
        string temp;
        in >> v.x >> temp >> v.y >> temp >> v.z;
        return in;
    }

    typedef Vector3<float> Vector3f;
    typedef Vector3f Point3f;
    typedef Vector3<double> Vector3d;
    typedef Vector3d Point3d;
}
#endif
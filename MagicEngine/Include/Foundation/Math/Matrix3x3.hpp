/**
 * @file Matrix3x3.hpp
 * @author xuyajie (xyjprogrammer@163.com)
 * @brief 列优先矩阵 4列3行
 * @version 0.1
 * @date 2022-06-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _MATRIX_3_X_3_HPP
#define _MATRIX_3_X_3_HPP

#include "Vector3.hpp"

namespace Magic
{

    template <typename T>
    class Vector3;

    template <typename T>
    class Matrix3x3
    {
    public:
        Matrix3x3(
            T m00, T m01, T m02, T m03,
            T m10, T m11, T m12, T m13,
            T m20, T m21, T m22, T m23);
        Matrix3x3(T m[9]);
        Matrix3x3();
        Matrix3x3 &Identity();
        void MakeRotation(const Vector3<T> &v, T theta);
        Vector3<T> operator*(const Vector3<T> &v) const;
        Matrix3x3<T> operator*(const Matrix3x3<T> &m) const;

        union
        {
            struct
            {
                T m00, m01, m02;
                T m10, m11, m12;
                T m20, m21, m22;
            };

            T m[9];
        };
    };

    template <typename T>
    Matrix3x3<T>::Matrix3x3(
        T m00, T m01, T m02, T m03,
        T m10, T m11, T m12, T m13,
        T m20, T m21, T m22, T m23) : m00(m00), m01(m01), m02(m02),
                                      m10(m10), m11(m11), m12(m12),
                                      m20(m20), m21(m21), m22(m22)
    {
    }

    template <typename T>
    Matrix3x3<T>::Matrix3x3(T m[9])
    {
        memcpy(this->m, m, sizeof(this->m));
    }

    template <typename T>
    Matrix3x3<T>::Matrix3x3()
        : m00(1), m01(0), m02(0),
          m10(0), m11(1), m12(0),
          m20(0), m21(0), m22(1)
    {
    }

    template <typename T>
    Matrix3x3<T> &Matrix3x3<T>::Identity()
    {
        memset(m, 0, sizeof(m));
        m[0] = m[4] = m[8] = static_cast<T>(1);
        return *this;
    }

    template <typename T>
    void Matrix3x3<T>::MakeRotation(const Vector3<T> &v, T theta)
    {
        T c = cos(theta);
        T s = sin(theta);
        T x2 = v.x * v.x;
        T y2 = v.y * v.y;
        T z2 = v.z * v.z;
        T xy = v.x * v.y;
        T xz = v.x * v.z;
        T yz = v.y * v.z;

        m00 = c + (1 - c) * x2;
        m01 = -v.z * s + (1 - c) * xy;
        m02 = v.y * s + (1 - c) * xz;
        m10 = v.z * s + (1 - c) * xy;
        m11 = c + (1 - c) * y2;
        m12 = -v.x * s + (1 - c) * yz;
        m20 = -v.y * s + (1 - c) * xz;
        m21 = v.x * s + (1 - c) * yz;
        m22 = c + (1 - c) * z2;
    }

    template <typename T>
    Vector3<T> Matrix3x3<T>::operator*(const Vector3<T> &v) const
    {
        return Vector3<T>(
            m00 * v.x + m01 * v.y + m02 * v.z,
            m10 * v.x + m11 * v.y + m12 * v.z,
            m20 * v.x + m21 * v.y + m22 * v.z);
    }

    template <typename T>
    Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T> &m) const
    {
        return Matrix3x3<T>(
            m00 * m.m00 + m01 * m.m10 + m02 * m.m20,
            m00 * m.m01 + m01 * m.m11 + m02 * m.m21,
            m00 * m.m02 + m01 * m.m12 + m02 * m.m22,

            m10 * m.m00 + m11 * m.m10 + m12 * m.m20,
            m10 * m.m01 + m11 * m.m11 + m12 * m.m21,
            m10 * m.m02 + m11 * m.m12 + m12 * m.m22,

            m20 * m.m00 + m21 * m.m10 + m22 * m.m20,
            m20 * m.m01 + m21 * m.m11 + m22 * m.m21,
            m20 * m.m02 + m21 * m.m12 + m22 * m.m22);
    }

    typedef Matrix3x3<float> Matrix3x3f;
    typedef Matrix3x3<double> Matrix3x3d;
}
#endif
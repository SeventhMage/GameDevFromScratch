#ifndef _QUATERNION_HPP_
#define _QUATERNION_HPP_

#include "Math.hpp"
#include "Vector3.hpp"
#include <cassert>
#include <cmath>

namespace Magic
{
    using namespace std;
    template <typename T>
    class Quaternion
    {
    public:
        Quaternion();
        Quaternion(T w, T x, T y, T z);

        void Identity();
        void Normalize();

        Vector3<T> ToEulerAngle();
        Quaternion &FromEulerAngle(T x, T y, T z);

        Quaternion &MakeRotateByX(T theta);
        Quaternion &MakeRotateByY(T theta);
        Quaternion &MakeRotateByZ(T theta);
        Quaternion &MakeRotateByAxis(const Vector3<T> &axis, T theta);
        T GetRotationAngle() const;
        Vector3<T> GetRotationAxis() const;

        Quaternion operator*(const Quaternion &q) const;
        Vector3<T> operator*(const Vector3<T> &v) const;

        static Quaternion Slerp(const Quaternion &q0, const Quaternion &q1, float t);

        template <typename T1>
        friend ostream &operator<<(ostream &out, const Quaternion<T1> &q);

    private:
        T w, x, y, z;
    };

    template <typename T>
    Quaternion<T>::Quaternion()
        : w(1), x(0), y(0), z(0)
    {
    }

    template <typename T>
    Quaternion<T>::Quaternion(T w, T x, T y, T z)
        : w(w), x(x), y(y), z(z)
    {
    }

    template <typename T>
    void Quaternion<T>::Identity()
    {
        w = static_cast<T>(1);
        x = y = z = static_cast<T>(0);
    }

    template <typename T>
    void Quaternion<T>::Normalize()
    {
        T mag = (T)sqrt(w * w + x * x + y * y + z * z);

        if (mag > 0)
        {
            T oneOverMag = (T)1 / mag;
            w *= oneOverMag;
            x *= oneOverMag;
            y *= oneOverMag;
            z *= oneOverMag;
        }
        else
        {
            assert(false);
            Identity();
        }
    }

    template <typename T>
    Vector3<T> Quaternion<T>::ToEulerAngle()
    {
        Vector3<T> euler;
        Quaternion &q = *this;
        T sp = (T)-2 * (q.y * q.z - q.w * q.x);
        if (fabs(sp) > (T)0.9999)
        {
            euler.y = PI_DIV_2 * sp;
            euler.x = atan2(-q.x + q.z + q.w * q.y, (T)0.5 - q.y * q.y - q.z * q.z);
            euler.z = 0;
        }
        else
        {
            euler.y = asin(sp);
            euler.x = atan2(q.x * q.z + q.w * q.y, (T)0.5 - q.x * q.x - q.y * q.y);
            euler.z = atan2(q.x * q.y + q.w * q.z, (T)0.5 - q.x * q.x - q.z * q.z);
        }

        return euler;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::FromEulerAngle(T x, T y, T z)
    {
        T hOver2 = (T)0.5 * y;
        T pOver2 = (T)0.5 * x;
        T bOver2 = (T)0.5 * z;

        T sh, sp, sb;
        T ch, cp, cb;

        sh = sin(hOver2);
        ch = cos(hOver2);
        sp = sin(pOver2);
        cp = cos(pOver2);
        sb = sin(bOver2);
        cb = cos(bOver2);

        this->w = ch * cp * cb + sh * sp * sb;
        this->x = ch * sp * cb + sh * cp * sb;
        this->y = -ch * sp * sb + sh * cp * cb;
        this->z = -sh * sp * cb + ch * cp * sb;

        return *this;
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::operator*(const Quaternion<T> &q) const
    {
        //右乘
        return Quaternion(w * q.w - x * q.x - y * q.y - z * q.z,
                          w * q.x + x * q.w + z * q.y - y * q.z,
                          w * q.y + y * q.w + x * q.z - z * q.x,
                          w * q.z + z * q.w + y * q.x - x * q.y);
    }

    template <typename T>
    Vector3<T> Quaternion<T>::operator*(const Vector3<T> &v) const
    {
        Quaternion vq(0, v.x, v.y, v.z);
        Quaternion invQ(w, -x, -y, -z);
        Quaternion result = invQ * vq * *this;

        return Vector3<T>(result.x, result.y, result.z);
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::MakeRotateByX(T theta)
    {
        T thetaOver2 = theta * (T)0.5;

        w = cos(thetaOver2);
        x = sin(thetaOver2);
        y = 0;
        z = 0;
        return *this;
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::MakeRotateByY(T theta)
    {
        T thetaOver2 = theta * (T)0.5;

        w = cos(thetaOver2);
        x = 0;
        y = sin(thetaOver2);
        z = 0;
        return *this;
    }
    template <typename T>
    Quaternion<T> &Quaternion<T>::MakeRotateByZ(T theta)
    {
        T thetaOver2 = theta * (T)0.5;

        w = cos(thetaOver2);
        x = 0;
        y = 0;
        z = sin(thetaOver2);
        return *this;
    }
    template <typename T>
    Quaternion<T> &Quaternion<T>::MakeRotateByAxis(const Vector3<T> &axis, T theta)
    {
        Vector3<T> axisNormallize = axis;
        axisNormallize.Normalize();

        T thetaOver2 = theta * (T)0.5;
        T sinThetaOver2 = sin(thetaOver2);

        w = cos(thetaOver2);
        x = axisNormallize.x * sinThetaOver2;
        y = axisNormallize.y * sinThetaOver2;
        z = axisNormallize.z * sinThetaOver2;
        return *this;
    }

    template <typename T>
    T Quaternion<T>::GetRotationAngle() const
    {
        T thetaOver2;
        if (w <= (T)-1)
            thetaOver2 = PI;
        else if (w >= (T)1)
            thetaOver2 = 0;
        else
            thetaOver2 = acos(w);
        return thetaOver2 * (T)2;
    }

    template <typename T>
    Vector3<T> Quaternion<T>::GetRotationAxis() const
    {
        T sinThetaOver2Sq = (T)1 - w * w;
        if (sinThetaOver2Sq <= 0)
        {
            return Vector3<T>(1, 0, 0);
        }

        T oneOverSinThetaOver2 = (T)1 / sqrt(sinThetaOver2Sq);
        return Vector3<T>(x * oneOverSinThetaOver2, y * oneOverSinThetaOver2, z * oneOverSinThetaOver2);
    }

    template <typename T>
    Quaternion<T> Quaternion<T>::Slerp(const Quaternion &q0, const Quaternion &q1, float t)
    {
        if (t <= 0)
            return q0;
        if (t >= (T)1)
            return q1;

        T cosOmega = q0.w * q1.w + q0.x * q1.x + q0.y * q1.y + q0.z * q1.z;
        T q1w = q1.w;
        T q1x = q1.x;
        T q1y = q1.y;
        T q1z = q1.z;
        if (cosOmega < 0)
        {
            q1w = -q1w;
            q1x = -q1x;
            q1y = -q1y;
            q1z = -q1z;
            cosOmega = -cosOmega;
        }

        assert(cosOmega < 1);

        T k0, k1;
        if (cosOmega > (T)0.9999)
        {
            k0 = (T)1 - t;
            k1 = t;
        }
        else
        {
            T sinOmega = sqrt((T)1 - cosOmega * cosOmega);
            T omega = atan2(sinOmega, cosOmega);
            T oneOverSinOmega = (T)1 / sinOmega;
            k0 = sin(((T)(1) - t) * omega) * oneOverSinOmega;
            k1 = sin(t * omega) * oneOverSinOmega;
        }

        return Quaternion(
            k0 * q0.w + k1 * q1w,
            k0 * q0.x + k1 * q1x,
            k0 * q0.y + k1 * q1y,
            k0 * q0.z + k1 * q1z);
    }

    template <typename T>
    ostream &operator<<(ostream &out, const Quaternion<T> &q)
    {
        out << q.w << "," << q.x << "," << q.y << "," << q.z;
        return out;
    }

    typedef Quaternion<double> Quaterniond;
    typedef Quaternion<float> Quaternionf;
}
#endif
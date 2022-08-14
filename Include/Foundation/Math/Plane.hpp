#ifndef _PLANE_HPP_
#define _PLANE_HPP_

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

#include <cmath>

namespace Magic
{
    template <typename T>
    class Plane
    {
    public:
        Plane();
        Plane(const Vector3<T> &normal, T distance);
        Plane(const Vector3<T> &normal, const Vector3<T> &point);

        T GetSignedDistance(const Vector3<T> &point) const;
        Vector3<T> GetMemberPoint();
        Vector3<T> &GetNormal() const;
        T GetDistance() const;

        void SetPlane(const Vector3<T> &p0, const Vector3<T> &p1, const Vector3<T> &p2);

        bool Intersect(const Ray<T> &ray, float *maxDistance = nullptr, Vector3<T> *intersection = nullptr) const;
        bool Intersect(const Sphere<T> &sphere) const;

        template <typename T1>
        friend ostream &operator<<(ostream &out, const Plane<T1> &plane);

    private:
        Vector3<T> _Normal;
        T _Distance;
    };

    template <typename T>
    Plane<T>::Plane()
        : _Normal(0, 0, 0), _Distance(0)
    {
    }

    template <typename T>
    Plane<T>::Plane(const Vector3<T> &normal, T distance)
        : _Normal(normal), _Distance(distance)
    {
    }
    template <typename T>
    Plane<T>::Plane(const Vector3<T> &normal, const Vector3<T> &point)
        : _Normal(normal), _Distance(point.DotProduct(normal))
    {
    }

    template <typename T>
    T Plane<T>::GetSignedDistance(const Vector3<T> &point) const
    {
        /**
         * p + an = q;
         * (p + an)*n = q * n;
         * p * n = (an) * n = q * n;
         * d + a = q * n;
         * a = q * n - d
         */
        return point.DotProduct(_Normal) - _Distance;
    }

    template <typename T>
    Vector3<T> Plane<T>::GetMemberPoint()
    {
        return -_Normal.DotProduct(_Distance);
    }

    template <typename T>
    Vector3<T> &Plane<T>::GetNormal() const
    {
        return _Normal;
    }
    template <typename T>
    T Plane<T>::GetDistance() const
    {
        return _Distance;
    }


    template <typename T>
    void Plane<T>::SetPlane(const Vector3<T> &p0, const Vector3<T> &p1, const Vector3<T> &p2)
    {
        Vector3<T> v0 = p1 - p0;
        Vector3<T> v1 = p2 - p0;
        _Normal = v0.CrossProduct(v1);
        _Normal.Normalize();
        _Distance = p0.DotProduct(_Normal);
    }

    template <typename T>
    bool Plane<T>::Intersect(const Ray<T> &ray, float *maxDistance, Vector3<T> *intersection) const
    {
        const Vector3<T> &rayOrigin = ray.Origin();
        const Vector3<T> &rayDir = ray.Direction();
        T toPlaneDis = GetSignedDistance(rayOrigin);
        if (toPlaneDis < 0 /*只和正平面相交*/ || (maxDistance && *maxDistance < toPlaneDis))
            return false;

        T angleCos = -rayDir.DotProduct(_Normal);
        //射线方向与平面平行
        if (FLOAT_EQUAL(angleCos, 0))
            return false;

        if (intersection)
        {
            *intersection = rayOrigin + rayDir * (toPlaneDis / angleCos);
        }

        return true;
    }

    template <typename T>
    bool Plane<T>::Intersect(const Sphere<T> &sphere) const
    {
        T distance = GetSignedDistance(sphere.Center());
        return std::abs(distance) < sphere.Radius;
    }

    template <typename T1>
    ostream &operator<<(ostream &out, const Plane<T1> &plane)
    {
        out << plane._Normal << ", " << plane._Distance;
        return out;
    }

    typedef Plane<double> Planed;
    typedef Plane<float> Planef;

}

#endif
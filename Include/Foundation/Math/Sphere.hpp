#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include "Vector3.hpp"
#include "Ray.hpp"

namespace Magic
{
    template <typename T>
    class Sphere
    {
    public:
        Sphere(const Vector3<T> &center, T radius);

        inline const Vector3<T> &Center() const { return _Center; }
        inline const T &Radius() const { return _Radius; }
        inline Vector3<T> &Center() { return _Center; }
        inline T &Radius() { return _Radius; }
        bool Intersect(const Ray<T> &ray, T *maxDistance = nullptr, Vector3<T> *intersection = nullptr) const;

        template <typename T1>
        friend ostream &operator<<(ostream &out, const Sphere<T1> &sphere);

    private:
        Vector3<T> _Center;
        T _Radius;
        float a;
    };

    template <typename T>
    Sphere<T>::Sphere(const Vector3<T> &center, T radius)
        : _Center(center), _Radius(radius)
    {
    }

    template <typename T>
    bool Sphere<T>::Intersect(const Ray<T> &ray, T *maxDistance, Vector3<T> *intersection) const
    {
        Vector3<T> rayDir = ray.Direction();
        rayDir.Normalize();
        Vector3<T> ray2Center = _Center - ray.Origin();
        T a = ray2Center.DotProduct(rayDir);
        T e2 = ray2Center.SqrLength();
        T a2 = a * a;
        T radius2 = _Radius * _Radius;
        T b2 = e2 - a2;

        if (b2 <= radius2)
        {
            if (maxDistance || intersection)
            {
                //射线点在球内，计算射出时的相交点
                T t = e2 < radius2 ? a + sqrt(radius2 - b2) : a - sqrt(radius2 - b2);
                if (maxDistance && *maxDistance < t)
                    return false;

                if (intersection)
                    *intersection = ray.Origin() + ray.Direction() * t;
            }
            return true;
        }

        return false;
    }

    template <typename T>
    ostream &operator<<(ostream &out, const Sphere<T> &sphere)
    {
        return out << sphere._Center << ", " << sphere._Radius;
    }

    typedef Sphere<double> Sphered;
    typedef Sphere<float> Spheref;
}

#endif
#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Plane.hpp"
#include "Math.hpp"
#include "Plane.hpp"

namespace Magic
{
    /**
     *               _V0
     *               /\
     *            e2/  \e1
     *             /    \
     *          _V1/______\_V2
     *               e0
     **/
    template <typename T>
    class Triangle
    {
    public:
        Triangle(const Vector3<T> &v0, const Vector3<T> &v1, const Vector3<T> v2);
        bool Contains(const Vector3<T> &point) const;
        //计算点out在三角形内的重心坐标，如果ou不在三角形所在的平面，则计算的为点在三角形平面上的投影点的重心坐标
        bool BarycentricCoord(const Vector3<T> &point, Vector3<T> &out) const;
        bool Intersect(const Ray<T> &ray, float *maxDistance = nullptr, Vector3<T> *intersection = nullptr) const;

        Vector3<T> &operator[](int i);
        const Vector3<T> &operator[](int i) const;

        template <typename T1>
        friend ostream &operator<<(ostream &out, const Triangle<T1> &tri);
    private:
        union
        {
            struct
            {
                Vector3<T> _V0, _V1, _V2;
            };
            Vector3<T> _V[3];
        };
    };

    template <typename T>
    Triangle<T>::Triangle(const Vector3<T> &v0, const Vector3<T> &v1, const Vector3<T> v2)
        : _V0(v0), _V1(v1), _V2(v2)
    {
    }

    template <typename T>
    bool Triangle<T>::BarycentricCoord(const Vector3<T> &point, Vector3<T> &out) const
    {
        Vector3<T> e0 = _V2 - _V1;
        Vector3<T> e1 = _V0 - _V2;
        Vector3<T> e2 = _V1 - _V0;
        Vector3<T> v0p = point - _V0;
        Vector3<T> v1p = point - _V1;
        Vector3<T> v2p = point - _V2;

        Vector3<T> dir = e2.CrossProduct(-e1);
        dir.Normalize();
        T area012_2 = e2.CrossProduct(-e1).Length();// DotProduct(dir);

        // 退化三角形，面积为0
        if (FLOAT_EQUAL(area012_2, 0))
            return false;

        //点在三角形外部时，至少有一个重心坐标值为负，
        T areaP01_2 = e2.CrossProduct(v0p).DotProduct(dir);
        T areaP12_2 = e0.CrossProduct(v1p).DotProduct(dir);
        T areaP20_2 = e1.CrossProduct(v2p).DotProduct(dir);

        T area012_2_inv = (T)1 / area012_2;
        out.x = areaP12_2 * area012_2_inv;
        out.y = areaP20_2 * area012_2_inv;
        out.z = areaP01_2 * area012_2_inv;

        return true;
    }

    template <typename T>
    bool Triangle<T>::Contains(const Vector3<T> &point) const
    {
        Vector3<T> e0 = _V2 - _V1;
        Vector3<T> e1 = _V0 - _V2;
        Vector3<T> e2 = _V1 - _V0;

        T area012_2 = e2.CrossProduct(-e1).Length();

        // 退化三角形，面积为0
        if (FLOAT_EQUAL(area012_2, 0))
            return false;

        Vector3<T> v0p = point - _V0;
        Vector3<T> v1p = point - _V1;
        Vector3<T> v2p = point - _V2;

        T areaP01_2 = e2.CrossProduct(v0p).Length();
        T areaP12_2 = e0.CrossProduct(v1p).Length();
        T areaP20_2 = e1.CrossProduct(v2p).Length();

        return FLOAT_EQUAL(areaP01_2 + areaP12_2 + areaP20_2 - area012_2, 0);
    }

    template <typename T>
    bool Triangle<T>::Intersect(const Ray<T> &ray, float *maxDistance, Vector3<T> *intersection) const
    {
        Vector3<T> e1 = _V2 - _V0;
        Vector3<T> e2 = _V1 - _V0;

        Vector3<T> normal = e2.CrossProduct(e1);
        Plane<T> plane(normal, _V0);
        Vector3<T> intersectionPoint;
        bool intersetWithPlane = plane.Intersect(ray, maxDistance, &intersectionPoint);
        if (intersetWithPlane)
        {
            bool result = Contains(intersectionPoint);
            if (result && intersection)
            {
                *intersection = intersectionPoint;
            }
            return result;
        }

        return false;
    }

    template <typename T>
    Vector3<T> &Triangle<T>::operator[](int i)
    {
        return _V[i];
    }

    template <typename T>
    const Vector3<T> &Triangle<T>::operator[](int i) const
    {
        return _V[i];
    }

    template <typename T>
    ostream &operator<<(ostream &out, const Triangle<T> &tri)
    {
        return out << tri._V0 << ", " << tri._V1 << ", " << tri._V2;
    }

    typedef Triangle<double> Triangled;
    typedef Triangle<float> Trianglef;
}

#endif
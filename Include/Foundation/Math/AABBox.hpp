#ifndef _AABB_BOX_HPP_
#define _AABB_BOX_HPP_

#include "Vector3.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Math.hpp"
#include "Plane.hpp"

namespace Magic
{

    template <typename T>
    class AABBox
    {
    public:
        AABBox(const Vector3<T> &min, const Vector3<T> &max);
        void Union(const Vector3<T> &point);
        void Union(const AABBox<T> &box);
        inline Vector3<T> Size() const;
        inline Vector3<T> Center() const;
        inline const Vector3<T> &Max() const;
        inline const Vector3<T> &Min() const;
        Vector3<T> ClosestPointTo(const Vector3<T> &point) const;
        bool Contains(const Vector3<T> &point) const;
        bool Intersect(const Sphere<T> &sphere) const;
        bool Intersect(const Ray<T> &ray, float *maxDistance = nullptr, Vector3<T> *intersection = nullptr) const;
        bool Intersect(const AABBox<T> &box, AABBox<T> *intersection = nullptr) const;

        template <typename T1>
        friend ostream &operator<<(ostream &out, const AABBox<T1> &v);
    private:
        Vector3<T> _Min;
        Vector3<T> _Max;
    };

    template <typename T>
    AABBox<T>::AABBox(const Vector3<T> &min, const Vector3<T> &max)
    {
        //保证传值不正确时得到合法的aabbox
        for (int i = 0; i < 3; ++i)
        {
            _Min[i] = MIN(min[i], max[i]);
            _Max[i] = MAX(min[i], max[i]);
        }
    }

    template <typename T>
    void AABBox<T>::Union(const Vector3<T> &point)
    {
        for (int i = 0; i < 3; ++i)
        {
            _Min[i] = MIN(_Min[i], point[i]);
            _Max[i] = MAX(_Max[i], point[i]);
        }
    }

    template <typename T>
    void AABBox<T>::Union(const AABBox<T> &box)
    {
        for (int i = 0; i < 3; ++i)
        {
            _Min[i] = MIN(_Min[i], box._Min[i]);
            _Max[i] = MAX(_Max[i], box._Max[i]);
        }
    }

    template <typename T>
    Vector3<T> AABBox<T>::Size() const
    {
        return _Max - _Min;
    }

    template <typename T>
    Vector3<T> AABBox<T>::Center() const
    {
        return (_Max + _Min) * (T)0.5;
    }

    template <typename T>
    const Vector3<T> &AABBox<T>::Max() const
    {
        return _Max;
    }
    template <typename T>
    const Vector3<T> &AABBox<T>::Min() const
    {
        return _Min;
    }

    template <typename T>
    Vector3<T> AABBox<T>::ClosestPointTo(const Vector3<T> &point) const
    {
        Vector3<T> result;
        for (int i = 0; i < 3; ++i)
        {
            if (point[i] < _Min[i])
                result[i] = _Min[i];
            else if (point[i] > _Max[i])
                result[i] = _Max[i];
            else
                result[i] = point[i];
        }
        return result;
    }

    template <typename T>
    bool AABBox<T>::Contains(const Vector3<T> &point) const
    {
        return point.x >= _Min.x && point.y >= _Min.y && point.z >= _Min.z && point.x <= _Max.x && point.y <= _Max.y && point.z <= _Max.z;
    }

    template <typename T>
    bool AABBox<T>::Intersect(const Sphere<T> &sphere) const
    {
        const Vector3<T> &sphereCenter = sphere.Center();
        Vector3<T> closestPoint = ClosestPointTo(sphereCenter);
        return (closestPoint - sphereCenter).SqrLength() < sphere.Radius();
    }

    template <typename T>
    bool AABBox<T>::Intersect(const Ray<T> &ray, float *maxDistance, Vector3<T> *intersection) const
    {
        Plane<T> planes[6] = {Plane<T>(-Vector3<T>::right, _Min), Plane<T>(-Vector3<T>::up, _Min), Plane<T>(-Vector3<T>::forward, _Min), 
            Plane<T>(Vector3<T>::right, _Max), Plane<T>(Vector3<T>::up, _Max), Plane<T>(Vector3<T>::forward, _Max)};
        
        for (int i = 0; i < 6; ++i)
        {
            Vector3<T> intersectPoint;
            if (planes[i].Intersect(ray, maxDistance, &intersectPoint))
            {
                bool contains = Contains(intersectPoint);
                if (contains)
                {
                    if (intersection) *intersection = intersectPoint;
                    return true;
                }
            }
        }

        return false;
    }

    template <typename T>
    bool AABBox<T>::Intersect(const AABBox<T> &box, AABBox *intersection) const
    {
        for (int i = 0; i < 3; ++i)
        {
            if (_Min[i] > box._Max[i])
                return false;
        }

        if (intersection)
        {
            for (int i = 0; i < 3; ++i)
            {
                intersection->_Min[i] = MAX(_Min[i], box._Min[i]);
                intersection->_Max[i] = MIN(_Max[i], box._Max[i]);
            }
        }

        return true;
    }

    template <typename T>
    ostream &operator<<(ostream &out, const AABBox<T> &v)
    {
        out << v._Min << ", " << v._Max;
        return out;
    }

    typedef AABBox<double> AABBoxd;
    typedef AABBox<float> AABBoxf;
}

#endif
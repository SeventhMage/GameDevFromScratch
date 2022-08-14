#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "Vector3.hpp"

namespace Magic
{
    template <typename T>
    class Ray
    {
    public:
        Ray();
        Ray(const Vector3<T> &origin, const Vector3<T> &direction);

        inline const Vector3<T> &Origin() const { return _Origin; }
        inline const Vector3<T> &Direction() const { return _Direction; }
        inline Vector3<T> &Origin() { return _Origin; }
        inline Vector3<T> &Direction() { return _Direction; }

        template <typename T1>
        friend ostream &operator<<(ostream &out, const Ray<T1> &ray);
    private:
        Vector3<T> _Origin;
        Vector3<T> _Direction;
    };

    template <typename T>
    Ray<T>::Ray()
        :_Origin(Vector3<T>(0, 0, 0)), _Direction(Vector3<T>(0, 0, -1))
    {
    }

    template <typename T>
    Ray<T>::Ray(const Vector3<T> &origin, const Vector3<T> &direction)
        :_Origin(origin), _Direction(direction)   
    {
    }

    template <typename T>
    ostream &operator<<(ostream &out, const Ray<T> &ray)
    {
        return out << ray._Origin << ", " << ray._Direction;
    }

    typedef Ray<double> Rayd;
    typedef Ray<float> Rayf;
}

#endif
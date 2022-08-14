#ifndef _MAGIC_FRUSTUM_HPP_
#define _MAGIC_FRUSTUM_HPP_

#include "Vector3.hpp"
#include "Matrix4x4.hpp"
#include "Plane.hpp"
#include "AABBox.hpp"

namespace Magic
{
    template <typename T>
    class Frustum
    {
    public:
        enum FPLANES
        {
            F_FAR_PLANE = 0,
            F_NEAR_PLANE,
            F_LEFT_PLANE,
            F_RIGHT_PLANE,
            F_BOTTOM_PLANE,
            F_TOP_PLANE,

            F_PLANE_COUNT
        };
        Frustum() {}
        ~Frustum() {}

        void Create(T fFov, T fAspect, T fNear, T fFar)
        {
            T xmin, xmax, ymin, ymax;
            T xFmin, xFmax, yFmin, yFmax;

            fNear = -fNear;
            fFar = -fFar;

            ymax = fNear * T(tan(fFov * 0.5f));
            ymin = -ymax;
            xmin = ymin * fAspect;
            xmax = -xmin;

            yFmax = fFar * T(tan(fFov * 0.5f));
            yFmin = -yFmax;
            xFmin = yFmin * fAspect;
            xFmax = -xFmin;

            _NLB.x = xmin;
            _NLB.y = ymin;
            _NLB.z = fNear;

            _NRB.x = xmax;
            _NRB.y = ymin;
            _NRB.z = fNear;

            _NRT.x = xmax;
            _NRT.y = ymax;
            _NRT.z = fNear;

            _NLT.x = xmin;
            _NLT.y = ymax;
            _NLT.z = fNear;

            _FLB.x = xFmin;
            _FLB.y = yFmin;
            _FLB.z = fFar;

            _FRB.x = xFmax;
            _FRB.y = yFmin;
            _FRB.z = fFar;

            _FRT.x = xFmax;
            _FRT.y = yFmax;
            _FRT.z = fFar;

            _FLT.x = xFmin;
            _FLT.y = yFmax;
            _FLT.z = fFar;

            CreatePlane();
        }

        bool Cull(const AABBox<T> &box) const
        {
            for (int i = 0; i < F_PLANE_COUNT; ++i)
            {
                if (_PlaneClip[i].GetSignedDistance(box.Min()) < 0 && _PlaneClip[i].GetSignedDistance(box.Max()) < 0)
                    return true;
            }
            return false;
        }

        bool CullSphere(const Vector3<T> &pos, T radius) const
        {
            for (int i = 0; i < F_PLANE_COUNT; ++i)
            {
                T dis = _PlaneClip[i].GetSignedDistance(pos);
                if (dis < -radius)
                    return true;
            }

            return false;
        }

        void TransformBy(const Matrix4x4<T> &mat4)
        {
            for (int i = 0; i < F_PLANE_COUNT; ++i)
            {
                mat4.Transform(_PlaneClip[i]);
            }
        }

    private:
        void CreatePlane()
        {
            // right hand
            _PlaneClip[F_NEAR_PLANE].SetPlane(_NRB, _NLB, _NRT);
            _PlaneClip[F_FAR_PLANE].SetPlane(_FLB, _FRB, _FRT);
            _PlaneClip[F_LEFT_PLANE].SetPlane(_NLB, _FLB, _NLT);
            _PlaneClip[F_RIGHT_PLANE].SetPlane(_NRB, _FRT, _FRB);
            _PlaneClip[F_TOP_PLANE].SetPlane(_NLT, _FRT, _NRT);
            _PlaneClip[F_BOTTOM_PLANE].SetPlane(_FRB, _FLB, _NLB);
        }

    private:
        Vector3<T> _NLB;
        Vector3<T> _NRB;
        Vector3<T> _NRT;
        Vector3<T> _NLT;
        Vector3<T> _FLB;
        Vector3<T> _FRB;
        Vector3<T> _FRT;
        Vector3<T> _FLT;

        Plane<T> _PlaneClip[F_PLANE_COUNT];
    };

    typedef Frustum<float> Frustumf;
    typedef Frustum<double> Frustumd;

}

#endif
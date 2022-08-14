#ifndef _MAGIC_C_CAMERA_H_
#define _MAGIC_C_CAMERA_H_

#include "Scene/ICamera.h"

namespace Magic
{
    class CCamera : public ICamera
    {
    public:
        CCamera(const CameraTypeParam &param);
        virtual ~CCamera();
        virtual void Update() = 0;
        virtual const Vector3f &GetPosition() const = 0;
        virtual const Vector3f &GetDirection() const = 0;
        virtual const Vector3f &GetUp() const = 0;
        virtual const CameraTypeParam &GetCameraTypeParam() const = 0;
        virtual CameraTypeParam &GetCameraTypeParam() = 0;
        virtual Matrix4x4f &GetViewMatrix() = 0;
        virtual Matrix4x4f &GetProjectionMatrix() = 0;
        virtual const Matrix4x4f &GetViewProjectionMatrix() const = 0;
        virtual const Frustumf &GetFrustum() const = 0;


        virtual void SetPosition(const Vector3f &position) = 0;
        virtual void SetDirection(const Vector3f &direction) = 0;
        virtual void SetUp(const Vector3f &up) = 0;
        virtual void SetCameraTypeParam(const CameraTypeParam &) = 0;

    private:
        CameraTypeParam _CameraTypeParam;
        Matrix4x4f _ViewMatrix;
        Matrix4x4f _ProjMatrix;
        Matrix4x4f _ViewProjMatrix;
        Vector3f _Position;
        Vector3f _Direction;
        Vector3f _Up;

        Frustumf _Frustum;

        bool _NeedUpdateView;
        bool _NeedUpdateProj;
    };
}

#endif
#ifndef _MAGIC_C_CAMERA_H_
#define _MAGIC_C_CAMERA_H_

#include "ICamera.h"
#include "Foundation/Object/IComponent.h"

namespace Magic
{
    class CCamera : public ICamera, public IComponent
    {
    public:
        CCamera(const CameraTypeParam &param);
        virtual ~CCamera();
        virtual void Update() ;
        virtual const Vector3f &GetPosition() const ;
        virtual const Vector3f &GetDirection() const ;
        virtual const Vector3f &GetUp() const ;
        virtual const CameraTypeParam &GetCameraTypeParam() const ;
        virtual CameraTypeParam &GetCameraTypeParam() ;
        virtual Matrix4x4f &GetViewMatrix() ;
        virtual Matrix4x4f &GetProjectionMatrix() ;
        virtual const Matrix4x4f &GetViewProjectionMatrix() const ;
        virtual const Frustumf &GetFrustum() const ;


        virtual void SetPosition(const Vector3f &position) ;
        virtual void SetDirection(const Vector3f &direction) ;
        virtual void SetUp(const Vector3f &up) ;
        virtual void SetCameraTypeParam(const CameraTypeParam &) ;

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
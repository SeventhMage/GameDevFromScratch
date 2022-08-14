#ifndef _MAGIC_I_CAMERA_H_
#define _MAGIC_I_CAMERA_H_

#include "Foundation/Math/Vector3.hpp"
#include "Foundation/Math/Matrix4x4.hpp"
#include "Foundation/Math/Frustum.hpp"

namespace Magic
{
    enum CameraType
    {
        Orthogonal= 0,
        Projection,
    };

    struct CameraTypeParam
    {
        union
        {
            struct 
            {
                float fov;
                float aspect;
            };

            struct
            {
                int width;
                int height;
            };
        };

        CameraType cameraType;
        float nearClip;
        float farClip;
        
    };

    class ICamera
    {
    public:
        virtual ~ICamera(){};
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

    };
}

#endif
#ifndef _MAGIC_I_TRANSORM_H_
#define _MAGIC_I_TRANSORM_H_

#include "IComponent.h"
#include "Foundation/Math/Matrix4x4.hpp"
#include "Foundation/Math/Vector3.hpp"
#include "Foundation/Math/Quaternion.hpp"

namespace Magic
{
    class ITransform : public IComponent
    {
    public:
        virtual const Matrix4x4f &GetWorld2LocalMatrix() const = 0;
        virtual const Matrix4x4f &GetLocal2WorldMatrix() const = 0;
        virtual const Vector3f &GetLocalPosition() const = 0;
        virtual const float GetLocalScale() const = 0;
        virtual const Quaternionf &GetLocalRotation() const = 0;
        virtual Vector3f GetWorldPosition() const = 0;
        virtual float GetWorldScale() const = 0;
        virtual Quaternionf GetWorldRotation() const = 0;
        virtual void SetLocalPosition(const Vector3f &) = 0;
        virtual void SetLocalScale(float scale) = 0;
        virtual void SetLocalRotation(const Quaternionf &) = 0;
        virtual void SetWorldPosition(const Vector3f &) = 0;
        virtual void SetWorldScale(float scale) = 0;
        virtual void SetWorldRotation(const Quaternionf &) = 0;
    };
}

#endif
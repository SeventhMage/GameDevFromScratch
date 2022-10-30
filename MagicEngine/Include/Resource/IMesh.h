#ifndef _MAGIC_I_MESH_H_
#define _MAGIC_I_MESH_H_

#include "IResource.h"
#include "Foundation/Math/Vector3.hpp"
#include "Foundation/Math/Vector2.hpp"
#include "Foundation/Object/IComponent.h"

namespace Magic
{
    class IMesh : public IResource
    {
    public:
        virtual ~IMesh() {}
        virtual Type GetType() const { return MESH; }
        virtual void SetVertices(Vector3f *, int) = 0;
        virtual void SetNormals(Vector3f *, int) = 0;
        virtual void SetColors(Vector3f *, int) = 0;
        virtual void SetIndices(int *, int) = 0;
        virtual void SetUVs(Vector2f *, int) = 0;
        virtual Vector3f *GetVertices() = 0;
        virtual Vector3f *GetNormals() = 0;
        virtual Vector3f *GetColors() = 0;
        virtual int *GetIndices() = 0;
        virtual Vector2f *GetUVs() = 0;
        virtual int GetVertexCount() = 0;
        virtual void Clear() = 0;
    };
}

#endif
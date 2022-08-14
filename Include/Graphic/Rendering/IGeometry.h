#ifndef _MAGIC_I_GEMOETRY_H_
#define _MAGIC_I_GEMOETRY_H_

#include "IVertexBuffer.h"
#include "IIndexBuffer.h"

namespace Magic
{
    class IGeometry
    {
    public:
        virtual ~IGeometry(){}
        virtual IVertexBuffer *GetVertexBuffer() const = 0;
        virtual IIndexBuffer *GetIndexBuffer() const = 0;
        virtual void Prepare() = 0;
    };
}

#endif
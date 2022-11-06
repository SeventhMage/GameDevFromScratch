#ifndef _MAGIC_I_VERTEX_BUFFER_H_
#define _MAGIC_I_VERTEX_BUFFER_H_

#include "RenderDefine.h"
#include "IVertexAttribute.h"

namespace Magic
{
    class IVertexBuffer
    {
    public:
        virtual ~IVertexBuffer() {}
        virtual void BufferData(void *data, int size, int offset = 0) = 0;
        virtual int GetVertexCount() const = 0;
        virtual IVertexAttribute *GetAttribute() const = 0;
        virtual void Prepare() = 0;
    };
}
#endif
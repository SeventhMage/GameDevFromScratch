#ifndef _MAGIC_C_VERTEX_BUFFER_H_
#define _MAGIC_C_VERTEX_BUFFER_H_

#include "Graphic/Rendering/IVertexBuffer.h"

namespace Magic
{
    class CVertexBuffer : public IVertexBuffer
    {
    public:
        CVertexBuffer();
        virtual IVertexAttribute *GetAttribute() const { return _VertexAttribute; }

    protected:
        IVertexAttribute *_VertexAttribute;
    };
}

#endif
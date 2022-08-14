#include "Graphic/Rendering/CGeometry.h"

namespace Magic
{
    CGeometry::CGeometry(IVertexBuffer *vertexBuffer, IIndexBuffer *indexBuffer)
        : _VertexBuffer(vertexBuffer), _IndexBuffer(indexBuffer)
    {
    }

    CGeometry::~CGeometry()
    {
        
    }

    IVertexBuffer *CGeometry::GetVertexBuffer() const
    {
        return _VertexBuffer;
    }
    IIndexBuffer *CGeometry::GetIndexBuffer() const
    {
        return _IndexBuffer;
    }

    void CGeometry::Prepare()
    {
        if (_VertexBuffer)
            _VertexBuffer->Prepare();
        if (_IndexBuffer)
            _IndexBuffer->Prepare();
    }
}
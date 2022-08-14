#ifndef _MAGIC_CGEOMETRY_H_
#define _MAGIC_CGEOMETRY_H_

#include "IGeometry.h"

namespace Magic
{
    class CGeometry : public IGeometry
    {
    public: 
        CGeometry(IVertexBuffer *, IIndexBuffer *);
        virtual ~CGeometry();
        virtual inline IVertexBuffer *GetVertexBuffer() const;
        virtual inline IIndexBuffer *GetIndexBuffer() const;
        virtual void Prepare();
    private:
        IVertexBuffer *_VertexBuffer;
        IIndexBuffer *_IndexBuffer;
    };
}

#endif
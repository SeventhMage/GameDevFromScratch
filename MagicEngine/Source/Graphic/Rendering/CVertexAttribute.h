#ifndef _MAGIC_C_VERTEX_ATTRIBUTE_H_
#define _MAGIC_C_VERTEX_ATTRIBUTE_H_

#include "Graphic/Rendering/IVertexAttribute.h"

namespace Magic
{
    class CVertexAttribute : public IVertexAttribute
    {
    public:
        CVertexAttribute();
        virtual ~CVertexAttribute();
        virtual void SetPositionAttr(int offset, int stride);
        virtual void SetNormalAttr(int offset, int stride);
        virtual void SetColorAttr(int offset, int stride);
        virtual void SetUVAttr(int offset, int stride);
        virtual int GetPositionOffset() const;
        virtual int GetPositionStride() const;
        virtual int GetNormalOffset() const;
        virtual int GetNormalStride() const;
        virtual int GetColorOffset() const;
        virtual int GetColorStride() const;
        virtual int GetUVOffset() const;
        virtual int GetUVStride() const;
        virtual bool HasPosition() const;
        virtual bool HasNormal() const;
        virtual bool HasColor() const;
        virtual bool HasUV() const;
    private:
        int _PositionOffset;
        int _PositionStride;
        int _NormalOffset;
        int _NormalStride;
        int _ColorOffset;
        int _ColorStride;
        int _UVOffset;
        int _UVStride;
    };
}

#endif
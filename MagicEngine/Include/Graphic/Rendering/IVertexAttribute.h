#ifndef _MAGIC_I_ATTRIBUTE_H_
#define _MAGIC_I_ATTRIBUTE_H_

namespace Magic
{
    class IVertexAttribute
    {
    public:
        virtual ~IVertexAttribute(){}
        virtual void SetPositionAttr(int offset, int stride) = 0;
        virtual void SetNormalAttr(int offset, int stride) = 0;
        virtual void SetColorAttr(int offset, int stride) = 0;
        virtual void SetUVAttr(int offset, int stride) = 0;
        virtual int GetPositionOffset() const = 0;
        virtual int GetPositionStride() const = 0;
        virtual int GetNormalOffset() const = 0;
        virtual int GetNormalStride() const = 0;
        virtual int GetColorOffset() const = 0;
        virtual int GetColorStride() const = 0;
        virtual int GetUVOffset() const = 0;
        virtual int GetUVStride() const = 0;
        virtual bool HasPosition() const = 0;
        virtual bool HasNormal() const = 0;
        virtual bool HasColor() const = 0;
        virtual bool HasUV() const = 0;
        virtual int GetOutSize() const = 0;
    };
}

#endif
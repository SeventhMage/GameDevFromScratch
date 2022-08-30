#include "CVertexAttribute.h"

namespace Magic
{

    CVertexAttribute::CVertexAttribute()
    :_PositionOffset(-1), _PositionStride(-1), _NormalOffset(-1), _NormalStride(-1), _ColorOffset(-1), _ColorStride(-1),_UVOffset(-1), _UVStride(-1)
    {
    }
    CVertexAttribute::~CVertexAttribute()
    {
    }
    void CVertexAttribute::SetPositionAttr(int offset, int stride)
    {
        _PositionOffset = offset;
        _PositionStride = stride;
    }
    void CVertexAttribute::SetNormalAttr(int offset, int stride)
    {
        _NormalOffset = offset;
        _NormalStride = stride;
    }
    void CVertexAttribute::SetColorAttr(int offset, int stride)
    {
        _ColorOffset = offset;
        _ColorStride = stride;
    }
    void CVertexAttribute::SetUVAttr(int offset, int stride)
    {
        _UVOffset = offset;
        _UVStride = stride;
    }

    int CVertexAttribute::GetPositionOffset() const
    {
        return _PositionOffset;
    }
    int CVertexAttribute::GetPositionStride() const
    {
        return _PositionStride;
    }
    int CVertexAttribute::GetNormalOffset() const
    {
        return _NormalOffset;
    }
    int CVertexAttribute::GetNormalStride() const
    {
        return _NormalStride;
    }
    int CVertexAttribute::GetColorOffset() const
    {
        return _ColorOffset;
    }
    int CVertexAttribute::GetColorStride() const
    {
        return _ColorStride;
    }
    int CVertexAttribute::GetUVOffset() const
    {
        return _UVOffset;
    }
    int CVertexAttribute::GetUVStride() const
    {
        return _UVStride;
    }

    bool CVertexAttribute::HasPosition() const
    {
        return _PositionOffset >= 0;
    }
    bool CVertexAttribute::HasNormal() const
    {
        return _NormalOffset >= 0;
    }
    bool CVertexAttribute::HasColor() const
    {
        return _ColorOffset >= 0;
    }
    bool CVertexAttribute::HasUV() const
    {
        return _UVOffset >= 0;
    }

    int CVertexAttribute::GetOutSize() const
    {
        int outSize = 0;
        if (HasPosition())
            outSize += sizeof(float) * 4;
        if (HasNormal())
            outSize += sizeof(float) * 3;
        if (HasColor())
            outSize += sizeof(float) * 4;
        if (HasUV())
            outSize += sizeof(float) * 2;
        return outSize;
    }
}
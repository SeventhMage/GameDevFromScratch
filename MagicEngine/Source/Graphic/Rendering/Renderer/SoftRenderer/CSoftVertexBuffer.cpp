#include "CSoftVertexBuffer.h"
#include "Foundation/Memory/Memory.h"

namespace Magic
{
    CSoftVertexBuffer::CSoftVertexBuffer()
        : _Buffer(nullptr), _Size(0), _VertexCount(0)
    {
    }
    CSoftVertexBuffer::~CSoftVertexBuffer()
    {
        SAFE_DELETE_ARRAY(_Buffer);
    }

    void CSoftVertexBuffer::BufferData(void *data, int size, int vertexCount)
    {
        if (_Size > 0 && _Size != size)
            SAFE_DELETE_ARRAY(_Buffer);
        _Buffer = NEW unsigned char[size];
        memcpy(_Buffer, data, size);
        _Size = size;
        _VertexCount = vertexCount;
    }

    int CSoftVertexBuffer::GetVertexCount() const
    {
        return _VertexCount;
    }

    Vector3f *CSoftVertexBuffer::GetPosition(int index)
    {
        assert(index >= 0 && index < _VertexCount);
        Vector3f *result = nullptr;
        if (_VertexAttribute->HasPosition())
        {
            int stride = _VertexAttribute->GetPositionStride();
            int offset = _VertexAttribute->GetPositionOffset();
            result = (Vector3f *)(_Buffer + stride * index + offset);
        }

        return result;
    }
    Vector3f *CSoftVertexBuffer::GetNormal(int index)
    {
        assert(index >= 0 && index < _VertexCount);

        Vector3f *result = nullptr;
        if (_VertexAttribute->HasNormal())
        {
            int stride = _VertexAttribute->GetNormalStride();
            int offset = _VertexAttribute->GetNormalOffset();
            result = (Vector3f *)(_Buffer + stride * index + offset);
        }

        return result;
    }
    Vector3f *CSoftVertexBuffer::GetColor(int index)
    {
        assert(index >= 0 && index < _VertexCount);

        Vector3f *result = nullptr;
        if (_VertexAttribute->HasColor())
        {
            int stride = _VertexAttribute->GetColorStride();
            int offset = _VertexAttribute->GetColorOffset();
            result = (Vector3f *)(_Buffer + stride * index + offset);
        }

        return result;
    }
    Vector2f *CSoftVertexBuffer::GetUV(int index)
    {
        assert(index >= 0 && index < _VertexCount);

        Vector2f *result = nullptr;
        if (_VertexAttribute->HasUV())
        {
            int stride = _VertexAttribute->GetUVStride();
            int offset = _VertexAttribute->GetUVOffset();
            result = (Vector2f *)(_Buffer + stride * index + offset);
        }
        return result;
    }

    std::vector<unsigned char> CSoftVertexBuffer::GetVertexData(int index)
    {
        int size = 0;
        Vector3f *position = GetPosition(index);
        Vector3f *normal = GetNormal(index);
        Vector3f *color = GetColor(index);
        Vector2f *uv = GetUV(index);
        if (position)
            size += sizeof(Vector3f);
        if (normal)
            size += sizeof(Vector3f);
        if (color)
            size += sizeof(Vector3f);
        if (uv)
            size += sizeof(Vector2f);
            
        std::vector<unsigned char> datas(size);
        size = 0;
        if (position)
        {
            memcpy(datas.data(), position, sizeof(Vector3f));
            size += sizeof(Vector3f);
        }
        if (normal)
        {
            memcpy(datas.data() + size, normal, sizeof(Vector3f));
            size += sizeof(Vector3f);
        }
        if (color)
        {
            memcpy(datas.data() + size, color, sizeof(Vector3f));
            size += sizeof(Vector3f);
        }
        if (uv)
        {
            memcpy(datas.data() + size, uv, sizeof(Vector2f));
            size += sizeof(Vector2f);
        }

        return datas;
    }
}
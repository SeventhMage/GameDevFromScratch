#include "CMesh.h"
#include "Foundation/Memory/Memory.h"
#include "Loader/CMeshLoader.hpp"

#include <cstring>

namespace Magic
{
    CMesh::CMesh()
        : _ResourceLoader(NEW CMeshLoader()), _Vertices(nullptr), _Normals(nullptr), 
            _Colors(nullptr), _UVs(nullptr), _Indices(nullptr), _VertexCount(0), _IndexCount(0),
            _AttributeBit(0)
    {
    }

    CMesh::~CMesh()
    {
        Clear();
        SAFE_DELETE(_ResourceLoader);
    }

    bool CMesh::Load(const char *fullPath)
    {
        return _ResourceLoader->Load(fullPath, this);
    }

    bool CMesh::Save(const char *fullPath)
    {
        return _ResourceLoader->Save(fullPath, this);
    }

    void CMesh::SetVertices(Vector3f *vertices, int size)
    {
        int vertexCount = size / sizeof(Vector3f);
        assert(_VertexCount == 0 || (_VertexCount > 0 && vertexCount == _VertexCount));
        _VertexCount = vertexCount;

        if (!_Vertices)
            _Vertices = NEW Vector3f[_VertexCount];
        memcpy(_Vertices, vertices, size);
        SetAttributeBit(AttributeBit::Vertex);
    }

    void CMesh::SetNormals(Vector3f *normals, int size)
    {
        int vertexCount = size / sizeof(Vector3f);
        assert(_VertexCount == 0 || (_VertexCount > 0 && vertexCount == _VertexCount));
        _VertexCount = vertexCount;
        if (!_Normals)
            _Normals = NEW Vector3f[vertexCount];
        memcpy(_Normals, normals, size);
        SetAttributeBit(AttributeBit::Normal);
    }

    void CMesh::SetColors(Vector3f *colors, int size)
    {
        int vertexCount = size / sizeof(Vector3f);
        assert(_VertexCount == 0 || (_VertexCount > 0 && vertexCount == _VertexCount));
        _VertexCount = vertexCount;

        if (!_Colors)
            _Colors = NEW Vector3f[vertexCount];
        memcpy(_Colors, colors, size);
        SetAttributeBit(AttributeBit::Color);
    }

    void CMesh::SetUVs(Vector2f *uvs, int size)
    {
        int vertexCount = size / sizeof(Vector2f);
        assert(_VertexCount == 0 || (_VertexCount > 0 && vertexCount == _VertexCount));
        _VertexCount = vertexCount;

        if (!_UVs)
            _UVs = NEW Vector2f[vertexCount];
        memcpy(_UVs, uvs, size);
        SetAttributeBit(AttributeBit::UV);
    }

    void CMesh::SetIndices(int *indices, int size)
    {
        int indexCount = size / sizeof(int);
        assert(_IndexCount == 0 || (_IndexCount > 0 && indexCount == _IndexCount));
        _IndexCount = indexCount;

        if (!_Indices)
            _Indices = NEW int[_IndexCount];
        memcpy(_Indices, indices, size);
    }

    Vector3f *CMesh::GetVertices() const
    {
        return _Vertices;
    }

    Vector3f *CMesh::GetNormals() const
    {
        return _Normals;
    }

    Vector3f *CMesh::GetColors() const
    {
        return _Colors;
    }

    Vector2f *CMesh::GetUVs() const
    {
        return _UVs;
    }

    int *CMesh::GetIndices() const
    {
        return _Indices;
    }

    int CMesh::GetVertexCount() const
    {
        return _VertexCount;
    }

    int CMesh::GetIndexCount() const
    {
        return _IndexCount;
    }

    void *CMesh::GetAttribute(int bit) const
    {
        switch (bit)
        {
        case AttributeBit::Vertex:
            return _Vertices;
        case AttributeBit::Normal:
            return _Normals;;
        case AttributeBit::Color:
            return _Colors;
        case AttributeBit::UV:
            return _UVs;
        }
        return nullptr;
    }

    int CMesh::GetAttributeBit() const
    {
        return _AttributeBit;
    }

    void CMesh::Clear()
    {
        SAFE_DELETE_ARRAY(_Vertices);
        SAFE_DELETE_ARRAY(_Normals);
        SAFE_DELETE_ARRAY(_Colors);
        SAFE_DELETE_ARRAY(_UVs);
        SAFE_DELETE_ARRAY(_Indices);
        _VertexCount = 0;
        _IndexCount = 0;
        _AttributeBit = 0;
    }

    void CMesh::SetAttributeBit(int bit)
    {
        _AttributeBit |= bit;
    }

}
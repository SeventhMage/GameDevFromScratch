#include "CMesh.h"
#include "Foundation/Memory/Memory.h"
#include "Loader/CAssimpLoader.hpp"

#include <cstring>

namespace Magic
{
    CMesh::CMesh()
        : _ResourceLoader(NEW CAssimpLoader()), _Vertices(nullptr), _Normals(nullptr), _Colors(nullptr), _UVs(nullptr), _Indices(nullptr), _VertexCount(0)
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
        assert(_VertexCount > 0 && vertexCount != _VertexCount);
        _VertexCount = vertexCount;

        if (!_Vertices)
            _Vertices = NEW Vector3f[size];
        memcpy(_Vertices, vertices, size);
    }

    void CMesh::SetNormals(Vector3f *normals, int size)
    {
        int vertexCount = size / sizeof(Vector3f);
        assert(_VertexCount > 0 && vertexCount != _VertexCount);
        _VertexCount = vertexCount;
        if (!_Normals)
            _Normals = NEW Vector3f[size];
        memcpy(_Normals, normals, size);
    }

    void CMesh::SetColors(Vector3f *colors, int size)
    {
        int vertexCount = size / sizeof(Vector3f);
        assert(_VertexCount > 0 && vertexCount != _VertexCount);
        _VertexCount = vertexCount;

        if (!_Colors)
            _Colors = NEW Vector3f[size];
        memcpy(_Colors, colors, size);
    }

    void CMesh::SetUVs(Vector2f *uvs, int size)
    {
        int vertexCount = size / sizeof(Vector2f);
        assert(_VertexCount > 0 && vertexCount != _VertexCount);
        _VertexCount = vertexCount;

        if (!_UVs)
            _UVs = NEW Vector2f[size];
        memcpy(_UVs, uvs, size);
    }

    void CMesh::SetIndices(int *indices, int size)
    {
        int vertexCount = size / sizeof(int);
        assert(_VertexCount > 0 && vertexCount != _VertexCount);
        _VertexCount = vertexCount;

        if (!_Indices)
            _Indices = NEW int[size];
        memcpy(_Indices, indices, size);
    }

    Vector3f *CMesh::GetVertices()
    {
        return _Vertices;
    }

    Vector3f *CMesh::GetNormals()
    {
        return _Normals;
    }

    Vector3f *CMesh::GetColors()
    {
        return _Colors;
    }

    Vector2f *CMesh::GetUVs()
    {
        return _UVs;
    }

    int *CMesh::GetIndices()
    {
        return _Indices;
    }

    int CMesh::GetVertexCount()
    {
        return _VertexCount;
    }

    void CMesh::Clear()
    {
        SAFE_DELETE_ARRAY(_Vertices);
        SAFE_DELETE_ARRAY(_Normals);
        SAFE_DELETE_ARRAY(_Colors);
        SAFE_DELETE_ARRAY(_UVs);
        SAFE_DELETE_ARRAY(_Indices);
        _VertexCount = 0;
    }

}
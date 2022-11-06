#ifndef _MAGIC_C_MESH_H_
#define _MAGIC_C_MESH_H_

#include "Resource/IMesh.h"
#include "Loader/IResourceLoader.h"

namespace Magic
{
    class CMesh : public IMesh
    {
    public:
        CMesh();
        virtual ~CMesh();
        virtual bool Load(const char *fullPath);
        virtual bool Save(const char *fullPath);
        virtual void SetVertices(Vector3f *, int);
        virtual void SetNormals(Vector3f *, int);
        virtual void SetColors(Vector3f *, int);
        virtual void SetUVs(Vector2f *, int);
        virtual void SetIndices(int *, int);
        virtual inline Vector3f *GetVertices() const;
        virtual inline Vector3f *GetNormals() const;
        virtual Vector3f *GetColors() const;
        virtual inline Vector2f *GetUVs() const;
        virtual inline int *GetIndices() const;
        virtual inline int GetVertexCount() const;
        virtual inline int GetIndexCount() const;
        virtual void *GetAttribute(int bit) const;
        virtual inline int GetAttributeBit() const;
        virtual void Clear();

        enum AttributeBit
        {
            Vertex = 1,
            Normal = 2,
            Color = 4,
            UV = 8,

            Count = 4
        };
    private:
        void SetAttributeBit(int bit);
    private:
        IResourceLoader *_ResourceLoader;
        Vector3f *_Vertices;
        Vector3f *_Normals;
        Vector3f *_Colors;
        Vector2f *_UVs;
        int *_Indices;
        int _VertexCount;
        int _IndexCount;
        int _AttributeBit;
    };
}

#endif
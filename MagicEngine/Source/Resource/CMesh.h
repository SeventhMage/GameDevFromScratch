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
        virtual inline Vector3f *GetVertices();
        virtual inline Vector3f *GetNormals();
        virtual Vector3f *GetColors();
        virtual inline Vector2f *GetUVs();
        virtual inline int *GetIndices();
        virtual inline int GetVertexCount();
        virtual void Clear();

    private:
        IResourceLoader *_ResourceLoader;
        Vector3f *_Vertices;
        Vector3f *_Normals;
        Vector3f *_Colors;
        Vector2f *_UVs;
        int *_Indices;
        int _VertexCount;
    };
}

#endif
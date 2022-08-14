#ifndef _MAGIC_C_MESH_H_
#define _MAGIC_C_MESH_H_

#include "IMesh.h"

namespace Magic
{
    class CMesh : public IMesh
    {
    public:
        CMesh();
        virtual ~CMesh();
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
        Vector3f *_Vertices;
        Vector3f *_Normals;
        Vector3f *_Colors;
        Vector2f *_UVs;
        int *_Indices;
        int _VertexCount;
    };
}

#endif
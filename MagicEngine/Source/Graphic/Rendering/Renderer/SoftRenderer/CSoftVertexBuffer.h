#ifndef _MAGIC_C_SOFT_VERTEX_BUFFER_H_
#define _MAGIC_C_SOFT_VERTEX_BUFFER_H_

#include "Graphic/Rendering/CVertexBuffer.h"
#include "Foundation/Math/Vector3.hpp"
#include "Foundation/Math/Vector2.hpp"

#include <vector>

namespace Magic
{
    class CSoftVertexBuffer : public CVertexBuffer
    {
    public:
        CSoftVertexBuffer();
        ~CSoftVertexBuffer();
        virtual void BufferData(void *data, int size, int vertexCount);
        virtual int GetVertexCount() const;
        virtual void Prepare(){}

        Vector3f *GetPosition(int index);
        Vector3f *GetNormal(int idnex);
        Vector3f *GetColor(int index);
        Vector2f *GetUV(int index);

        std::vector<unsigned char> GetVertexData(int index);
    private:
        unsigned char *_Buffer;
        int _Size;
        int _VertexCount;
    };
}

#endif
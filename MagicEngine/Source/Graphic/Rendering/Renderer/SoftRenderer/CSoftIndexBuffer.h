#ifndef _MAGIC_C_SOfT_INDEX_BUFFER_H_
#define _MAGIC_C_SOfT_INDEX_BUFFER_H_

#include "Graphic/Rendering/CIndexBuffer.h"

namespace Magic
{
    class CSoftIndexBuffer : public CIndexBuffer
    {
    public:
        CSoftIndexBuffer(int size, int indexCount);
        ~CSoftIndexBuffer();
        virtual void BufferData(void *data);
        virtual inline int GetIndexCount() const { return _IndexCount; }
        virtual void Prepare();

        unsigned int GetIndex(int i);
    private:
        unsigned char *_Buffer;
        int _Size;
        int _IndexCount;
    };
}

#endif
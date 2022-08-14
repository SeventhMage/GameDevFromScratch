#ifndef _MAGIC_C_SOfT_INDEX_BUFFER_H_
#define _MAGIC_C_SOfT_INDEX_BUFFER_H_

#include "Graphic/Rendering/CIndexBuffer.h"

namespace Magic
{
    class CSoftIndexBuffer : public CIndexBuffer
    {
    public:
        CSoftIndexBuffer();
        ~CSoftIndexBuffer();
        virtual void BufferData(void *data, int size, int indexCount);
        virtual inline int GetIndexCount() const { return _IndexCount; }
        virtual void Prepare();

    private:
        unsigned char *_Buffer;
        int _Size;
        int _IndexCount;
    };
}

#endif
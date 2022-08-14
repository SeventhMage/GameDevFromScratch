#include "CSoftIndexBuffer.h"
#include "Foundation/Memory/Memory.h"

namespace Magic
{
    CSoftIndexBuffer::CSoftIndexBuffer()
        : _Buffer(nullptr), _Size(0), _IndexCount(0)
    {
    }
    CSoftIndexBuffer::~CSoftIndexBuffer()
    {
        SAFE_DELETE_ARRAY(_Buffer);
    }

    void CSoftIndexBuffer::BufferData(void *data, int size, int indexCount)
    {
        if (_Size > 0 && _Size != size)
            SAFE_DELETE_ARRAY(_Buffer);
        _Buffer = NEW unsigned char[size];
        memcpy(_Buffer, data, size);
        _Size = size;
        _IndexCount = indexCount;
    }

    void CSoftIndexBuffer::Prepare()
    {

    }
}
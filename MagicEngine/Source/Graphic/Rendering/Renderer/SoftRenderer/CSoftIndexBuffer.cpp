#include "CSoftIndexBuffer.h"
#include "Foundation/Memory/Memory.h"

namespace Magic
{
    CSoftIndexBuffer::CSoftIndexBuffer(int size, int indexCount)
        : _Buffer(NEW unsigned char[size]), _Size(size), _IndexCount(indexCount)
    {
    }
    CSoftIndexBuffer::~CSoftIndexBuffer()
    {
        SAFE_DELETE_ARRAY(_Buffer);
    }

    void CSoftIndexBuffer::BufferData(void *data)
    {
        memcpy(_Buffer, data, _Size);
    }

    void CSoftIndexBuffer::Prepare()
    {

    }

    unsigned int CSoftIndexBuffer::GetIndex(int i)
    {
        return *((unsigned int *)_Buffer + i);
    }
}
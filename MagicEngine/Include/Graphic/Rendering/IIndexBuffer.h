#ifndef _MAGIC_I_INDEX_BUFFER_H_
#define _MAGIC_I_INDEX_BUFFER_H_

namespace Magic
{
    class IIndexBuffer
    {
    public:
        virtual ~IIndexBuffer(){}
        virtual void BufferData(void *data) = 0;
        virtual int GetIndexCount() const = 0;
        virtual void Prepare() = 0;
    };
}

#endif
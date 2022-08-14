#ifndef _MAGIC_C_OBJECT_H_
#define _MAGIC_C_OBJECT_H_

namespace Magic
{
    class CObject
    {
    public:
        virtual ~CObject(){}
        virtual int GetInstanceID();
    };
}

#endif
#ifndef _MAGIC_I_OBJECT_H_
#define _MAGIC_I_OBJECT_H_

namespace Magic
{
    class IObject
    {
    public:
        virtual ~IObject(){}
        virtual int GetInstanceID() = 0;
    };
}

#endif
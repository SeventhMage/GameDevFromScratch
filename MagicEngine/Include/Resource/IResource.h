#ifndef _MAGIC_I_RESOURCE_H_
#define _MAGIC_I_RESOURCE_H_

namespace Magic
{
    class IResource
    {
    public:
        virtual ~IResource(){}
        virtual bool Load(const char *fullPath) = 0;
    };
}

#endif
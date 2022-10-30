#ifndef _MAGIC_I_RESOURCE_H_
#define _MAGIC_I_RESOURCE_H_

namespace Magic
{
    class IResource
    {
    public:
        enum Type
        {
            MATERIAL,
            MESH,
            IMAGE,
            SHADER,
        };
        virtual ~IResource(){}
        virtual Type GetType() const = 0;
        virtual bool Load(const char *fullPath) = 0;
        virtual bool Save(const char *fullPath) = 0;
    };
}

#endif
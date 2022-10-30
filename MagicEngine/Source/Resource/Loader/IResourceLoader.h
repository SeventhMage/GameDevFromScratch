#ifndef _MAGIC_I_RESOURCE_LOADER_H_
#define _MAGIC_I_RESOURCE_LOADER_H_

#include "Resource/IResource.h"

namespace Magic
{
    class IResourceLoader
    {
    public:
        virtual ~IResourceLoader(){}
        virtual bool Load(const char *filePath, IResource *resource) = 0;
        virtual bool Save(const char *filePath, IResource *resource) = 0;
    };
}

#endif
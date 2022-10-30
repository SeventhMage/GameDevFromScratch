#ifndef _MAGIC_C_ASSIMP_LOADER_HPP_
#define _MAGIC_C_ASSIMP_LOADER_HPP_

#include "IResourceLoader.h"

namespace Magic
{
    class CAssimpLoader : public IResourceLoader
    {
    public:
        bool Load(const char *filePath, IResource *resource)
        {
            if (resource->GetType() == IResource::Type::MESH)
            {
                return true;
            }
            return false;
        }

        bool Save(const char *filePath, IResource *resource)
        {
            if (resource->GetType() == IResource::Type::MESH)
            {
                return true;
            }
            return false;
        }
    };
}

#endif
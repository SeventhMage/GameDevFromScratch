#ifndef _MAGIC_C_ASSIMP_LOADER_HPP_
#define _MAGIC_C_ASSIMP_LOADER_HPP_

#include "IResourceLoader.h"
#include "Dependency/assimp/Importer.hpp"
#include "Dependency/assimp/scene.h"
#include "Dependency/assimp/postprocess.h"
#include "Debugger/LogUtils.h"

namespace Magic
{
    class CAssimpLoader : public IResourceLoader
    {
    public:
        bool Load(const char *filePath, IResource *resource)
        {
            if (resource->GetType() == IResource::Type::MESH)
            {
                Assimp::Importer importer;
                const aiScene *scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs)
                if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
                {
                    LogError("CAssimpLoader::Load Error, %s\n", filePath);
                }
                
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
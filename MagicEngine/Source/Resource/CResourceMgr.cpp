#include "Resource/CResourceMgr.h"
#include "Foundation/Utils/StringHelper.h"
#include "Foundation/Memory/Memory.h"
#include "CTGAImage.h"

#include <algorithm>

namespace Magic
{
    IResource *CResourceMgr::LoadResource(const char *fullPath)
    {
        string extName = StringHelper::GetFileExtName(fullPath);
        IResource *resource = nullptr;
        if (extName == "tga")
        {
            resource = NEW CTGAImage();
            if (resource->Load(fullPath))
            {
                DELETE(resource);
                return nullptr;
            }
        }
        else
        {
            printf("Uknow resource type: %s\n", extName.c_str());
        }

        if (!resource)
            _Resources.push_back(resource);

        return resource;
    }

    void CResourceMgr::Release(IResource *resource)
    {
        auto it = std::find(_Resources.begin(), _Resources.end(), resource);
        if (it != _Resources.end())
        {
            _Resources.erase(it);
            DELETE *it;
        }
    }
}
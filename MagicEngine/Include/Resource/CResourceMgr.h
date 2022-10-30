#ifndef _MAGIC_C_RESOURCE_MGR_H_
#define _MAGIC_C_RESOURCE_MGR_H_

#include "IResource.h"
#include "Foundation/Utils/Singleton.hpp"
#include "IMaterial.h"
#include "IMesh.h"
#include "IShader.h"

#include <vector>

namespace Magic
{
    class CResourceMgr : public Singleton<CResourceMgr>
    {
    public:
        ~CResourceMgr(){}
        IResource *LoadResource(const char *fullPath);
        void Release(IResource *resource);

        IMaterial *CreateMaterial();
    private:
        std::vector<IResource *> _Resources;
    };
}

#endif
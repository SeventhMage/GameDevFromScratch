#ifndef _MAGIC_C_RESOURCE_MGR_H_
#define _MAGIC_C_RESOURCE_MGR_H_

#include "IResource.h"
#include "Foundation/Utils/Singleton.hpp"
#include <vector>

namespace Magic
{
    class CResourceMgr : public Singleton<CResourceMgr>
    {
    public:
        ~CResourceMgr(){}
        virtual IResource *LoadResource(const char *fullPath);
        virtual void Release(IResource *resource);
    private:
        std::vector<IResource *> _Resources;
    };
}

#endif
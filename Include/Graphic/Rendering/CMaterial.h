#ifndef _MAGIC_C_MATERIAL_H_
#define _MAGIC_C_MATERIAL_H_

#include <memory>

#include "IMaterial.h"

namespace Magic
{
    class CMaterial : public IMaterial
    {
    public:
        CMaterial();
        virtual ~CMaterial();
        virtual void SetShader(IShader *, EShader);
    private:
        IShader *_Shaders[EShader::Count];
    };
}

#endif
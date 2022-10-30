#include "CMaterial.h"
#include "Foundation/Memory/Memory.h"
#include "Loader/CNlohmannLoader.hpp"

namespace Magic
{
    CMaterial::CMaterial()
    :_ResourceLoader(NEW CNlohmannloader())
    ,_isTransparent(false)
    {
    }
    CMaterial::~CMaterial()
    {
        DELETE _ResourceLoader;
    }

    bool CMaterial::Load(const char *fullPath)
    {
        return _ResourceLoader->Load(fullPath, this);
    }

    bool CMaterial::Save(const char *fullPath)
    {
        return _ResourceLoader->Save(fullPath, this);
    }

    void CMaterial::SetName(const char *name)
    {
        _Name = name;
    }
    void CMaterial::SetVertShader(const char *name)
    {
        _VertShader = name;
    }
    void CMaterial::SetFragShader(const char *name)
    {
        _FragShader = name;
    }

    void CMaterial::SetTexture(int slot, const char *name)
    {
        _Textures[slot] = name;
    }

    void CMaterial::SetTransparent(bool transparent)
    {
        _isTransparent = transparent;
    }

    const char *CMaterial::GetName() const
    {
        return _Name.c_str();
    }
    const char *CMaterial::GetVertShader() const
    {
        return _VertShader.c_str();
    }
    const char *CMaterial::GetFragShader() const
    {
        return _FragShader.c_str();
    }
    const char *CMaterial::GetTexture(int slot) const
    {
        auto it = _Textures.find(slot);
        if (it != _Textures.end())
            return it->second.c_str();
        return nullptr;
    }

    int CMaterial::GetTextureQuantity() const
    {
        return _Textures.size();
    }

    bool CMaterial::IsTransparent() const
    {
        return _isTransparent;
    }
}
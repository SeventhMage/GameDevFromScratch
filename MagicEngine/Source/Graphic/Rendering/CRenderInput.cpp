#include <cassert>
#include <cstring>
#include "Graphic/Rendering/CRenderInput.h"


namespace Magic
{
    CRenderInput::CRenderInput()
    :_Geometry(nullptr), _ShaderProgram(nullptr)
    {
        memset(_Textures, 0, sizeof(_Textures));
    }
    CRenderInput::~CRenderInput()
    {
    }
    void CRenderInput::SetGeometry(IGeometry * geo)
    {
        _Geometry = geo;
    }
    void CRenderInput::SetShaderProgram(IShaderProgram * program)
    {
        _ShaderProgram = program;
    }

    void CRenderInput::SetTexture(int slot, ITexture *texture)
    {
        assert(slot >= 0 && slot < MAX_TEXTURE_NUM);
        _Textures[slot] = texture;
    }

    IGeometry *CRenderInput::GetGeometry() const
    {
        return _Geometry;
    }

    ITexture *CRenderInput::GetTexture(int slot) const
    {
        assert(slot >= 0 && slot < MAX_TEXTURE_NUM);
        return _Textures[slot];
    }

    IShaderProgram *CRenderInput::GetShaderProgram() const
    {
        return _ShaderProgram;
    }

    void CRenderInput::Prepare()
    {
        if (_Geometry)
            _Geometry->Prepare();
        if (_ShaderProgram)
            _ShaderProgram->Prepare();
        for (int i = 0; i < MAX_TEXTURE_NUM; ++i)
        {
            if (_Textures[i])
                _Textures[i]->Prepare();
        }
    }
}
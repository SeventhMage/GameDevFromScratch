#ifndef _MAGIC_C_MATERIAL_H_
#define _MAGIC_C_MATERIAL_H_

#include <string>
#include <map>

#include "Resource/IMaterial.h"
#include "Loader/IResourceLoader.h"

using namespace std;

namespace Magic
{
    class CNlohmannloader;
    class CMaterial : public IMaterial
    {
    public:
        CMaterial();
        virtual ~CMaterial();
        virtual bool Load(const char *fullPath);
        virtual bool Save(const char *fullPath);

        virtual void SetName(const char *name);
        virtual void SetVertShader(const char *name);
        virtual void SetFragShader(const char *name);
        virtual void SetTransparent(bool transparent);
        virtual void SetTexture(int slot, const char *name);
        virtual const char *GetName() const;
        virtual const char *GetVertShader() const;
        virtual const char *GetFragShader() const;
        virtual const char *GetTexture(int slot) const;
        virtual int GetTextureQuantity() const;
        virtual bool IsTransparent() const;
    private:
        friend class CNlohmannloader;
        IResourceLoader *_ResourceLoader;
        string _Name;
        string _VertShader;
        string _FragShader;
        map<int, string> _Textures;

        bool _isTransparent;
    };
}

#endif
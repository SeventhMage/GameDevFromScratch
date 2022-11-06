#ifndef _MAGIC_C_NLOHMANN_LOADER_HPP_
#define _MAGIC_C_NLOHMANN_LOADER_HPP_

#include "IResourceLoader.h"
#include "Dependency/nlohmann/json.hpp"
#include "../CMaterial.h"

#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

namespace Magic
{
    class CNlohmannloader : public IResourceLoader
    {
    public:
        bool Load(const char *filePath, IResource *resource)
        {
            if (resource->GetType() == IResource::Type::MATERIAL)
            {
                CMaterial *res = (CMaterial *)resource;
                try
                {
                    ifstream i(filePath);
                    json j;
                    i >> j;
                    j.at("Name").get_to(res->_Name);
                    j.at("Vert").get_to(res->_VertShader);
                    j.at("Frag").get_to(res->_FragShader);
                    j.at("Transparent").get_to(res->_isTransparent);
                    j.at("Textures").get_to(res->_Textures);
                    i.close();
                }
                catch (const exception &e)
                {
                    cerr << e.what() << endl;
                    return false;
                }
                return true;
            }
            return false;
        }

        bool Save(const char *filePath, IResource *resource)
        {

            if (resource->GetType() == IResource::Type::MATERIAL)
            {
                CMaterial *res = (CMaterial *)resource;
                try
                {
                    ofstream o(filePath);
                    json j;
                    j["Name"] = res->_Name;
                    j["Vert"] = res->_VertShader;
                    j["Frag"] = res->_FragShader;
                    j["Transparent"] = res->_isTransparent;
                    j["Textures"] = res->_Textures;

                    o << j;

                    o.close();
                }
                catch (const exception &e)
                {
                    cerr << e.what() << endl;
                    return false;
                }
                return true;
            }
            return false;
        }
    };
}

#endif

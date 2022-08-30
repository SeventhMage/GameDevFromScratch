#include "Graphic/Rendering/CSoftProgram.h"
#include "Foundation/Memory/Memory.h"

namespace Magic
{
    IMPLEMENT_INITIALIZE(CSoftProgram);
    IMPLEMENT_TERMINATE(CSoftProgram);

    map<string, CSoftProgram::VProgram> *CSoftProgram::_pVPrograms = nullptr;
    map<string, CSoftProgram::FProgram> *CSoftProgram::_pFPrograms = nullptr;
    void CSoftProgram::Initialize()
    {
        _pVPrograms = NEW map<string, VProgram>;
        _pFPrograms = NEW map<string, FProgram>;
    }

    void CSoftProgram::Terminate()
    {
        SAFE_DELETE(_pVPrograms);
        SAFE_DELETE(_pFPrograms);
    }

    void CSoftProgram::RegisterVProgram(const char *name, VProgram vProgram)
    {
        _pVPrograms->insert(make_pair(name, vProgram));
    }
    void CSoftProgram::RegisterFProgram(const char *name, FProgram fProgram)
    {
        _pFPrograms->insert(make_pair(name, fProgram));
    }

    CSoftProgram::VProgram CSoftProgram::GetVProgram(const char *name)
    {
        auto iter = _pVPrograms->find(name);
        if (iter != _pVPrograms->end())
        {
            return iter->second;
        }
        return nullptr;
    }

    CSoftProgram::FProgram CSoftProgram::GetFProgram(const char *name)
    {
        auto iter = _pFPrograms->find(name);
        if (iter != _pFPrograms->end())
        {
            return iter->second;
        }
        return nullptr;
    }
}
#include "Foundation/System/CMain.h"
#include "Foundation/Memory/Memory.h"

namespace Magic
{
    CMain::InitializerArray *CMain::_initializers = nullptr;
    CMain::TerminatorArray *CMain::_terminators = nullptr;

    void CMain::AddInitializer(Initializer initializer)
    {
        if (!_initializers)
            _initializers = NEW InitializerArray;
        _initializers->push_back(initializer);
    }
    void CMain::AddTerminator(Terminator terminator)
    {
        if (!_terminators)
            _terminators = NEW TerminatorArray;
        _terminators->push_back(terminator);
    }
    void CMain::Initialize()
    {
        if (_initializers)
        {
            for (std::size_t i = 0; i < _initializers->size(); ++i)
            {
                (*_initializers)[i]();
            }
            DELETE(_initializers);
            _initializers = nullptr;
        }
    }
    void CMain::Terminate()
    {
        if (_terminators)
        {
            for (std::size_t i = 0; i < _terminators->size(); ++i)
            {
                (*_terminators)[i]();
            }

            DELETE(_terminators);
            _terminators = nullptr;
        }
    }
}
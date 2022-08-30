#ifndef _MAGIC_C_SOFT_PROGRAM_H_
#define _MAGIC_C_SOFT_PROGRAM_H_

#include "ISampler.h"
#include "Foundation/System/MainMCR.h"

#include <string>
#include <map>

using namespace std;

namespace Magic
{
    class CSoftProgram
    {
        DECLARE_INITIALIZE;
        DECLARE_TERMINATE;
    public:
        typedef void (*VProgram)(const void*, const void *, const void *, unsigned char*);
        typedef Color (*FProgram)(const void*, const void *, ISampler**, const void*);

        static void RegisterVProgram(const char *name, VProgram vProgram);
        static void RegisterFProgram(const char *name, FProgram fProgram);
        static VProgram GetVProgram(const char *name);
        static FProgram GetFProgram(const char *name);

    private:
        static map<string, VProgram> *_pVPrograms;
        static map<string, FProgram> *_pFPrograms;
    };

    REGISTER_INITIALIZE(CSoftProgram);
    REGISTER_TERMINATE(CSoftProgram);
}

#endif
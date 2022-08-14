#ifndef _MAGIC_C_MAIN_H_
#define _MAGIC_C_MAIN_H_

#include <vector>

namespace Magic
{
    class CMain
    {
    public:
        typedef void (*Initializer)(void);
        typedef std::vector<Initializer> InitializerArray;
        typedef void (*Terminator)(void);
        typedef std::vector<Terminator> TerminatorArray;

        static void AddInitializer(Initializer);
        static void AddTerminator(Terminator);
        
        static void Initialize();
        static void Terminate();
    private:
        static InitializerArray *_initializers;
        static TerminatorArray *_terminators;
    };
}

#endif
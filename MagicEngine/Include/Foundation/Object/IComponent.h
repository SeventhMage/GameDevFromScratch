#ifndef _MAGIC_I_COMPONENT_H_
#define _MAGIC_I_COMPONENT_H_

namespace Magic
{
    class IComponent 
    {
    public:
        virtual ~IComponent(){}
        virtual void Update() = 0;
    };
}

#endif
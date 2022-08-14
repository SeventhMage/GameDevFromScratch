#ifndef _OBBOX_HPP_
#define _OBBOX_HPP_

#include "Vector3.hpp"

namespace Magic
{
    template <typename T>
    class OBBox
    {

    private:
        Vector3<T> _Center;
        Vector3<T> _Length;
        Vector3<T> _Width;
        Vector3<T> _Height;
    };
}

#endif
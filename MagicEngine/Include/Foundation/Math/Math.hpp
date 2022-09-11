#ifndef _MATH_HPP_
#define _MATH_HPP_

namespace Magic
{
    #define PI 3.141592654
    #define PI_2 (2 * PI)
    #define PI_DIV_2 (PI / 2)
    #define PI_DIV_3 (PI / 3)
    #define PI_DIV_6 (PI / 6)
    #define FLOAT_EPSINON 1e-5

    #define MIN(a, b) ((a) <= (b) ? (a) : (b))
    #define MAX(a, b) ((a) >= (b) ? (a) : (b))
    #define CLAMP(c, a, b) (MIN(MAX(c, a), b))
    #define FLOAT_EQUAL(a, b) ((a) - (b) > -FLOAT_EPSINON && (a) - (b) < FLOAT_EPSINON)


}



#endif
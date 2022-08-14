#ifndef _MAGIC_UTILS_HPP_
#define _MAGIC_UTILS_HPP_

namespace Magic
{
    class Utils
    {
    public:
        template <typename T>
        static inline void Swap(T &a, T &b)
        {
            T c = a;
            a = b;
            b = c;
        }

        static inline float InvSqrt(float x)
        {
            float xhalf = 0.5f * x;
            int i = *(int *)&x;             // get bits for floating VALUE
            i = 0x5f375a86 - (i >> 1);      // gives initial guess y0
            x = *(float *)&i;               // convert bits BACK to float
            x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
            return x;
        }
    };
}

#endif
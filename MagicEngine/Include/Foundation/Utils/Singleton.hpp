#ifndef _MAGIC_SINGLETON_HPP_
#define _MAGIC_SINGLETON_HPP_

namespace Magic
{
    template <typename T>
    class Singleton
    {
    public:
        static T *Instance()
        {
            static T instance;
            return &instance;
        }
    protected:
        Singleton<T>() {}
        ~Singleton<T>() {}
    private:
        Singleton<T>(const Singleton<T> &) {}
        Singleton<T> &operator=(const Singleton<T> &) { return *this; }
    };
}

#endif
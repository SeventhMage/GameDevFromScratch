#ifndef _MAGIC_MEMORY_H_
#define _MAGIC_MEMORY_H_

#include <memory>
#include <cstring>

namespace Magic
{
#define NEW new
#define DELETE delete
#define SAFE_DELETE(p) \
    if (p)             \
    {                  \
        DELETE p;      \
        p = nullptr;   \
    }

#define SAFE_DELETE_ARRAY(p) \
    if (p)                   \
    {                        \
        DELETE[] p;          \
        p = nullptr;         \
    }
}

#endif
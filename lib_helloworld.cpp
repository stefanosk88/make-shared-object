#include <string>
#include <cstdio>

#include "lib_helloworld.h"

static std::string g_helloMsg("Hello shared obj World");

#ifdef __cplusplus
extern "C"
{
#endif
    _EXPORT void printHello(void)
    {
        printf("%s\n", g_helloMsg.c_str());
    }
#ifdef __cplusplus
}
#endif

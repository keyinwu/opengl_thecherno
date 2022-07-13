#ifndef UTILS_H__
#define UTILS_H__

#define ASSERT(x) if (!(x)) assert(false)
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLCheckErro())

#endif
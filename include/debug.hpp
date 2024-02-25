#pragma once

#include <GLFW/glfw3.h>

void clear_error();
GLenum glCheckError_(const char *file, int line);

#ifdef __DEBUG__

// ASSERT and GLCALL macros
#define ASSERT(x)                                                              \
    if (!(x))                                                                  \
        __asm__ volatile("int $0x03");

#define GLCALL(x)                                                              \
    clear_error();                                                             \
    x;                                                                         \
    glCheckError_(__FILE__, __LINE__)
// ASSERT(glCheckError_(__FILE__, __LINE__) != GL_NO_ERROR)

// glCheckError macro
#define glCheckError()                                                         \
    clear_error();                                                             \
    glCheckError_(__FILE__, __LINE__)

// LOG macro
#define LOG(x)                                                                 \
    std::cout << x << std::endl; // idk why but neovim :make command doesnt see
                                 // output when it aint endl

// #define LOG(x) std::cout << x << "\n";

#else

#define glCheckError()
#define ASSERT(x)
#define LOG(x)
#define GLCALL(x) x

#endif

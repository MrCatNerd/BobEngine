#include <iostream>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "debug.hpp"

void clear_error() {
    while (glGetError() != GL_NO_ERROR)
        ;
}

GLenum glCheckError_(const char *file, int line) {
    GLenum errorCode;
    static unsigned long errorCount = 0;

    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            error = "STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error = "STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        default:
            error = "Unrecognized error code";
            break;
        }

        errorCount++;
        if (errorCount <= 10)
            std::cout << "[OpenGL Error] " << error << " | " << file << ":"
                      << line << " (error count: " << errorCount
                      << " | error code:" << errorCode << ")" << std::endl;
    }
    return errorCode;
}

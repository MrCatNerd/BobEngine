#include <iostream>

#include "utils.hpp"
#include "debug.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <GLFW/glfw3.h>

/// Don`t you worry 'bout it
void EngineError(const std::string &error_msg) {
    std::cerr << error_msg << std::endl;
    glfwTerminate();
    exit(-1);
}

/// Get the content of a file
std::string GetFile(const std::string &path) {
    std::string content;
    std::ifstream file(path);

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            content = buffer.str();
            file.close();
            LOG("[DEBUG] " + std::string("File '") + path +
                "' successfully read");
        } else {
            std::cerr << "Unable to open file '" << path << "'" << std::endl;
        }
    } catch (std::ifstream::failure e) {
        std::cout << "[FS ERROR] FILE_READ::FILE_NOT_SUCCESFULLY_READ"
                  << std::endl;
    }

    return content;
}

/// Takes a symbolic type constant and returns its size
/// Probably missing a few types but those were the most important
unsigned long get_gl_type_size(unsigned int type) {
    switch (type) {
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
        return sizeof(GLbyte);
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
        return sizeof(GLshort);
    case GL_INT_2_10_10_10_REV:
    case GL_INT:
    case GL_UNSIGNED_INT_2_10_10_10_REV:
    case GL_UNSIGNED_INT:
        return sizeof(GLint);
    case GL_FLOAT:
        return sizeof(GLfloat);
    case GL_DOUBLE:
        return sizeof(GLdouble);
    case GL_FIXED:
        return sizeof(GLfixed);
    case GL_HALF_FLOAT:
        return sizeof(GLhalf);
    }

    return 0;
}

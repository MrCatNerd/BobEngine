#include "Shader.h"
#include "BobUtils.h"
#include "spdlog/spdlog.h"

namespace Bob {

static unsigned int compileShader(unsigned int type, const char *contents);

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
    : programID(0), vertexPath(vertexPath), fragmentPath(fragmentPath) {
    spdlog::debug("Creating shader from: '{:s}' (vert) & '{:s}' (frag",
                  vertexPath, fragmentPath);

    // read and compile vertex shader
    const std::string vertexStr = ReadFile(this->vertexPath);
    unsigned int vertexShader =
        Bob::compileShader(GL_VERTEX_SHADER, vertexStr.c_str());

    // read and compile fragment shader
    const std::string fragmentStr = ReadFile(this->fragmentPath);
    unsigned int fragmentShader =
        Bob::compileShader(GL_FRAGMENT_SHADER, fragmentStr.c_str());

    this->programID = glCreateProgram();
    glAttachShader(this->programID, vertexShader);
    glAttachShader(this->programID, fragmentShader);
    glLinkProgram(this->programID);

    int success;
    char infoLog[512];
    glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->programID, 512, NULL, infoLog);

        spdlog::error("Shader linking failed: '{:s}'\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

static unsigned int compileShader(unsigned int type, const char *contents) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &contents, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::string typeName = "UnknownType";

        switch (type) {
        case GL_VERTEX_SHADER:
            typeName = "Vertex";
            break;
        case GL_FRAGMENT_SHADER:
            typeName = "Fragment";
            break;
        default:
            break;
        }

        spdlog::error("{:s} shader compilation failed: '{:s}'\n", typeName,
                      infoLog);
    }

    return shader;
}

} // namespace Bob

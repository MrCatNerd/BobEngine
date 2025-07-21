#include "Shader.h"
#include "BobUtils.h"

#include <spdlog/spdlog.h>
#include <glm/ext.hpp>

namespace Bob {

static unsigned int compileShader(unsigned int type, const char *contents);

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
    : programID(0), vertexPath(vertexPath), fragmentPath(fragmentPath) {
    spdlog::debug("Creating shader from: '{:s}' (vert) & '{:s}' (frag)",
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
    glShaderSource(shader, 1, &contents, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
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

int Shader::getUniformLocation(const std::string &string) {
    if (this->uniformCache.find(string) != this->uniformCache.end())
        return this->uniformCache[string];

    const int location = glGetUniformLocation(this->programID, string.c_str());
    if (location < 0)
        spdlog::error("Uniform variable '{:s}' doesn't exist (s{:d})", string,
                      this->programID);
    else {
        this->uniformCache[string] = location;
    }

    return location;
}

void Shader::setUniformBool(const std::string &name, bool value) {
    glUniform1i(this->getUniformLocation(name), value);
}
void Shader::setUniform1i(const std::string &name, int value) {
    glUniform1i(this->getUniformLocation(name), value);
}
void Shader::setUniform1f(const std::string &name, float value) {
    glUniform1f(this->getUniformLocation(name), value);
}

void Shader::setUniform3f(const std::string &name, float v0, float v1,
                          float v2) {
    glUniform3f(this->getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2,
                          float v3) {
    glUniform4f(this->getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniformMatrix4fv(const std::string &name, glm::mat4 value) {
    glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE,
                       glm::value_ptr(value));
}

void Shader::setUniformMatrix3fv(const std::string &name, glm::mat3 value) {
    glUniformMatrix3fv(this->getUniformLocation(name), 1, GL_FALSE,
                       glm::value_ptr(value));
}

} // namespace Bob

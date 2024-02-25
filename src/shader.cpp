#include <GL/glew.h>

#include "include/shader.hpp"
#include "include/debug.hpp"

unsigned int Shader::create_shader(const char *shader_src, int type) const {
    unsigned int shader = glCreateShader(type);
    GLCALL(glShaderSource(shader, 1, &shader_src, nullptr));
    GLCALL(glCompileShader(shader));

    int success;
    char infoLog[512];
    GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

    if (!success) {
        GLCALL(glGetShaderInfoLog(shader, 512, nullptr, infoLog));
        LOG("ERROR::SHADER_PROGRAM::COMPILATION_FAILED " << infoLog);
    }

    return shader;
}

unsigned int Shader::compile_shader() const {
    unsigned int vertexShader =
        create_shader(vert_str.c_str(), GL_VERTEX_SHADER);
    LOG("Vertex shader was compiled successfully");

    unsigned int fragmentShader =
        create_shader(frag_str.c_str(), GL_FRAGMENT_SHADER);
    LOG("Fragment shader was compiled successfully");

    unsigned int id = glCreateProgram();
    GLCALL(glAttachShader(id, vertexShader));
    GLCALL(glAttachShader(id, fragmentShader));
    GLCALL(glLinkProgram(id));
    GLCALL(glValidateProgram(id));

    int success;
    char infoLog[512];
    GLCALL(glGetProgramiv(id, GL_LINK_STATUS, &success));

    if (!success) {
        GLCALL(glGetProgramInfoLog(id, 512, nullptr, infoLog));
        LOG("ERROR::SHADER_PROGRAM::LINKING_FAILED " << infoLog);
    }

    GLCALL(glDeleteShader(vertexShader));
    GLCALL(glDeleteShader(fragmentShader));

    return id;
}

Shader::Shader(const std::string &vert_str, const std::string &frag_str)
    : vert_str(vert_str), frag_str(frag_str) {
    m_id = compile_shader();
}

void Shader::set_Uniform4f(const std::string &name, float v0, float v1,
                           float v2, float v3) const {
    GLCALL(glUniform4f(get_uniform_location(name), v0, v1, v2,
                       v3)); // Transfer the uniform data to the shader
}

/**
 * @brief Returns an integer that represents the location of a specific uniform
 * variable within a program object
 *
 * @param name
 * @return A location for a shader uniform thingy
 */
unsigned int Shader::get_uniform_location(const std::string &name) const {
    return glGetUniformLocation(m_id, name.c_str());
}

void Shader::bind() const { GLCALL(glUseProgram(m_id)); }
void Shader::unbind() const { GLCALL(glUseProgram(0)); }

Shader::~Shader() { GLCALL(glDeleteProgram(m_id)); }

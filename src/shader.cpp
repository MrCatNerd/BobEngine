#include <GL/glew.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

#include "shader.hpp"
#include "debug.hpp"

unsigned int Shader::create_shader(const char *shader_src, int type) {
    GLCALL(unsigned int shader = glCreateShader(type));
    GLCALL(glShaderSource(shader, 1, &shader_src, NULL));
    GLCALL(glCompileShader(shader));

    int success;
    char infoLog[512];
    GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

    if (!success) {
        GLCALL(glGetShaderInfoLog(shader, 512, nullptr, infoLog));
        switch (type) {
        case GL_VERTEX_SHADER:
            LOG("[OpenGL Error] FRAGMENT_SHADER::COMPILATION_FAILED "
                << infoLog);
            break;
        case GL_FRAGMENT_SHADER:
            LOG("[OpenGL Error] VERTEX_SHADER::COMPILATION_FAILED " << infoLog);
            break;
        }
    } else
        switch (type) {
        case GL_VERTEX_SHADER:
            LOG("[DEBUG] Vertex shader #" << shader
                                          << " was compiled successfully");
            break;
        case GL_FRAGMENT_SHADER:
            LOG("[DEBUG] Fragment shader #" << shader
                                            << " was compiled successfully");
            break;
        }

    return shader;
}

unsigned int Shader::compile_shaders() {
    unsigned int vertexShader =
        Shader::create_shader(m_vert_str.c_str(), GL_VERTEX_SHADER);

    unsigned int fragmentShader =
        Shader::create_shader(m_frag_str.c_str(), GL_FRAGMENT_SHADER);

    unsigned int id = glCreateProgram();
    GLCALL(glAttachShader(id, vertexShader));
    GLCALL(glAttachShader(id, fragmentShader));
    GLCALL(glLinkProgram(id));

    // error handling stuff
    GLCALL(glValidateProgram(id));

    int success;
    char infoLog[512];
    GLCALL(glGetProgramiv(id, GL_LINK_STATUS, &success));

    if (!success) {
        GLCALL(glGetProgramInfoLog(id, 512, nullptr, infoLog));
        LOG("[OpenGL Error] SHADER_PROGRAM::LINKING_FAILED " << infoLog);
    }

    // bind the current id
    GLCALL(glUseProgram(id));

    // delete the shaders (not the program)
    GLCALL(glDeleteShader(vertexShader));
    GLCALL(glDeleteShader(fragmentShader));

    return id;
}

Shader::Shader(const std::string &vert_str, const std::string &frag_str)
    : m_vert_str(vert_str), m_frag_str(frag_str) {
    this->m_id = compile_shaders();
}

// general datatypes
void Shader::set_UniformBool(const std::string &name, bool value) const {
    GLCALL(glUniform1i(this->get_uniform_location(name), value));
}
void Shader::set_Uniform1i(const std::string &name, int value) const {
    GLCALL(glUniform1i(this->get_uniform_location(name), value));
}
void Shader::set_Uniform1f(const std::string &name, float value) const {
    GLCALL(glUniform1f(this->get_uniform_location(name), value));
}

// vectors
void Shader::set_Uniform3f(const std::string &name, float v0, float v1,
                           float v2) const {
    GLCALL(glUniform3f(this->get_uniform_location(name), v0, v1, v2));
}

void Shader::set_Uniform4f(const std::string &name, float v0, float v1,
                           float v2, float v3) const {
    GLCALL(glUniform4f(this->get_uniform_location(name), v0, v1, v2, v3));
}

void Shader::set_UniformMatrix4fv(const std::string &name,
                                  glm::mat4 value) const {
    GLCALL(glUniformMatrix4fv(this->get_uniform_location(name), 1, GL_FALSE,
                              glm::value_ptr(value)));
}

void Shader::set_UniformMatrix3fv(const std::string &name,
                                  glm::mat3 value) const {
    GLCALL(glUniformMatrix3fv(this->get_uniform_location(name), 1, GL_FALSE,
                              glm::value_ptr(value)));
}

int Shader::get_uniform_location(const std::string &name) const {

    if (this->uniform_location_cache.find(name) !=
        this->uniform_location_cache.end())
        return this->uniform_location_cache[name];

    int location = glGetUniformLocation(this->m_id, name.c_str());

    if (location == -1)
        LOG("[WARNING] uniform variable " << name << " doesn't exist");

    this->uniform_location_cache[name] = location;

    return location;
}

Shader::~Shader() { GLCALL(glDeleteProgram(m_id)); }

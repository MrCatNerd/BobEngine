#include <GL/glew.h>
#include <unordered_map>

#include "shader.hpp"
#include "debug.hpp"

unsigned int Shader::create_shader(const char *shader_src, int type) const {
    unsigned int shader = glCreateShader(type);
    GLCALL(glShaderSource(shader, 1, &shader_src, nullptr));
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
            LOG("Vertex shader was compiled successfully");
            break;
        case GL_FRAGMENT_SHADER:
            LOG("Fragment shader was compiled successfully");
            break;
        }

    return shader;
}

unsigned int Shader::compile_shader() const {
    unsigned int vertexShader =
        create_shader(vert_str.c_str(), GL_VERTEX_SHADER);

    unsigned int fragmentShader =
        create_shader(frag_str.c_str(), GL_FRAGMENT_SHADER);

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
        LOG("[OpenGL Error] SHADER_PROGRAM::LINKING_FAILED " << infoLog);
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
                           float v2, float v3) {
    GLCALL(glUniform4f(get_uniform_location(name), v0, v1, v2, v3));
}

int Shader::get_uniform_location(const std::string &name) {
    static std::unordered_map<std::string, unsigned int> uniform_location_cache;

    if (uniform_location_cache.find(name) != uniform_location_cache.end())
        return uniform_location_cache[name];

    GLCALL(int location = glGetUniformLocation(m_id, name.c_str()));
    if (location == -1)
        LOG("[WARNING] uniform variable " << name << " doesn't exist");
    uniform_location_cache[name] = location;
    return location;
}

void Shader::bind() const { GLCALL(glUseProgram(m_id)); }
void Shader::unbind() const { GLCALL(glUseProgram(0)); }

Shader::~Shader() { GLCALL(glDeleteProgram(m_id)); }

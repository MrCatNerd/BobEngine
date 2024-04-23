#pragma once

#include <string>
#include <GL/glew.h>

#include "debug.hpp"

class Shader {
    private:
        const std::string &m_vert_str;
        const std::string &m_frag_str;

        unsigned int m_id = 0;

    public:
        Shader(const std::string &vert_str, const std::string &frag_str);

        inline void bind() const { GLCALL(glUseProgram(this->m_id)); };
        inline static void unbind() { GLCALL(glUseProgram(0)); };

        void set_Uniform4f(const std::string &name, float v0, float v1,
                           float v2, float v3);

        inline unsigned int get_id() const { return m_id; }

        ~Shader();

    protected:
        static unsigned int create_shader(const char *shader_src, int type);
        int get_uniform_location(const std::string &name);
        unsigned int compile_shaders();
};

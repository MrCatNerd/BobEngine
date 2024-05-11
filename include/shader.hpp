#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <string>
#include <GL/glew.h>
#include <unordered_map>

#include "debug.hpp"

class Shader {
    private:
        const std::string &m_vert_str;
        const std::string &m_frag_str;

        mutable std::unordered_map<std::string, int> uniform_location_cache;

        unsigned int m_id = 0;

    public:
        Shader(const std::string &vert_str, const std::string &frag_str);

        inline void bind() const { GLCALL(glUseProgram(this->m_id)); };
        inline static void unbind() { GLCALL(glUseProgram(0)); };

        void set_Uniform4f(const std::string &name, float v0, float v1,
                           float v2, float v3) const;
        void set_UniformBool(const std::string &name, bool value) const;
        void set_Uniform1i(const std::string &name, int value) const;
        void set_Uniform1f(const std::string &name, float value) const;
        void set_Uniform3f(const std::string &name, float v0, float v1,
                           float v2) const;
        void set_UniformMatrix4fv(const std::string &name,
                                  glm::mat4 value) const;
        void set_UniformMatrix3fv(const std::string &name,
                                  glm::mat3 value) const;

        inline unsigned int get_id() const { return m_id; }

        ~Shader();

    private:
        static unsigned int create_shader(const char *shader_src, int type);
        int get_uniform_location(const std::string &name) const;
        unsigned int compile_shaders();
};

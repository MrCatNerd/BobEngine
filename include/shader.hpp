#pragma once

#include <string>

class Shader {
    private:
        std::string vert_str;
        std::string frag_str;

        unsigned int m_id = 0;

    public:
        Shader(const std::string &vert_str, const std::string &frag_str);

        void bind() const;
        static void unbind();

        void set_Uniform4f(const std::string &name, float v0, float v1,
                           float v2, float v3);

        inline unsigned int get_id() const { return m_id; }

        ~Shader();

    private:
        unsigned int compile_shaders();
        static unsigned int create_shader(const char *shader_src, int type);
        int get_uniform_location(const std::string &name);
};

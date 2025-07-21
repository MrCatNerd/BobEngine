#pragma once

#include <string>
#include <glad/glad.h>
#include <unordered_map>

namespace Bob {

class Shader {
    private:
        unsigned int programID;

        std::unordered_map<std::string, int> uniformCache;

    public:
        const std::string vertexPath;
        const std::string fragmentPath;

        Shader(const std::string &vertexPath, const std::string &fragmentPath);
        ~Shader(void) { glDeleteProgram(this->programID); }
        void use(void) const { glUseProgram(this->programID); }
        static void unuse(void) { glUseProgram(0); }
        unsigned int getProgramID(void) const { return this->programID; }

        int getUniformLocation(const std::string &string);
        void setUniformBool(const std::string &name, bool value);
        void setUniform1i(const std::string &name, int value);
        void setUniform1f(const std::string &name, float value);
        void setUniform3f(const std::string &name, float v0, float v1,
                          float v2);
        void setUniform4f(const std::string &name, float v0, float v1, float v2,
                          float v3);
        void setUniformMatrix4fv(const std::string &name, glm::mat4 value);
        void setUniformMatrix3fv(const std::string &name, glm::mat3 value);
};

} // namespace Bob

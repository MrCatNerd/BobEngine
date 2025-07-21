#pragma once

#include <string>
#include <glad/glad.h>

namespace Bob {

class Shader {
    private:
        unsigned int programID;

    public:
        const std::string vertexPath;
        const std::string fragmentPath;

        Shader(const std::string &vertexPath, const std::string &fragmentPath);
        ~Shader(void) { glDeleteProgram(this->programID); }
        void use(void) const { glUseProgram(this->programID); }
        static void unuse(void) { glUseProgram(0); }
        unsigned int getProgramID(void) const { return this->programID; }
};

} // namespace Bob

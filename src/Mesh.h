#pragma once

#include <vector>

#include "Shader.h"
#include "Window.h"

namespace Bob {

class Mesh {
    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        unsigned int elementCount;

    public:
        Mesh(const std::vector<float> &vertices,
             const std::vector<int> &indices);
        static Mesh LoadFromFile(const std::string &path);
        ~Mesh(void);

        void render(const Shader &shader) const;
};

} // namespace Bob

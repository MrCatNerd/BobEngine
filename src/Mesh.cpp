#include "Mesh.h"

#include "Shader.h"
#include "spdlog/spdlog.h"

#include <vector>

namespace Bob {

Mesh::Mesh(const std::vector<float> &vertices, const std::vector<int> &indices)
    : VAO(0), VBO(0), EBO(0), elementCount(0) {
    spdlog::debug("Creating mesh");

    // create VAO
    spdlog::trace("Creating Mesh VAO");
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    // create VBO
    spdlog::trace("Creating Mesh VBO");
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // create EBO
    spdlog::trace("Creating Mesh EBO");
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
                 indices.data(), GL_STATIC_DRAW);
    this->elementCount = indices.size();

    // unbind all
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh(void) {
    spdlog::trace("Destroying mesh");
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

void Mesh::render(const Shader &shader) const {
    shader.use();
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->elementCount, GL_UNSIGNED_INT, 0);

    // unbind
    glBindVertexArray(0);
    Shader::unuse();
}

} // namespace Bob

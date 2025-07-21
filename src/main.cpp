#include "BobEngine.h"
#include "Shader.h"
#include "Mesh.h"

#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>

int main(void) {
    {
        Bob::Engine engine;

        Bob::Shader shader("res/shaders/vertex.glsl",
                           "res/shaders/fragment.glsl");
        const std::vector<float> vertices{
            // positions         // colors
            0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
            0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
        };
        const std::vector<int> indices{
            0, 1, 3, // first triangle
        };
        Bob::Mesh mesh(vertices, indices);

        spdlog::debug("Starting main loop");

        while (!engine.window->shouldClose()) {
            engine.window->clear(glm::sin(glfwGetTime()), 0.7f, 0.2f, 1.0f);

            // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            shader.use();
            shader.setUniform4f("color", 0.0f, 1.0f, 0.0f, 1.0f);
            mesh.render(shader);

            engine.window->flip();
            engine.window->poll();
        }

        spdlog::debug("Finished main loop");
    }

    return 0;
}

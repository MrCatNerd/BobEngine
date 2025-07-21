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
            0.5f,  0.5f,  0.0f, // top right
            0.5f,  -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f,  0.0f  // top left
        };
        const std::vector<int> indices{
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        Bob::Mesh mesh(vertices, indices);

        spdlog::debug("Starting main loop");

        // TODO: timer class
        double lastTime = glfwGetTime();
        while (!engine.window->shouldClose()) {
            const double deltaTime = glfwGetTime() - lastTime;

            engine.window->clear(glm::sin(glfwGetTime()), 0.7f, 0.2f, 1.0f);

            mesh.render(shader);

            engine.window->flip();
            engine.window->poll();
            lastTime = glfwGetTime();
        }

        spdlog::debug("Finished main loop");
    }

    return 0;
}

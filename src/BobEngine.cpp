#include "BobEngine.h"

#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Bob {

Engine::Engine(void) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::debug("Initalizing Engine...");

    spdlog::debug("Initalizing GLFW");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if TARGET_OS == MacOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    this->window = new Window("BobEngine", 1000, 1000);

    spdlog::debug("Finished: Initalizing Engine");
}

Engine::~Engine(void) {
    spdlog::debug("Terminating Engine");

    free(this->window);

    spdlog::debug("Terminating GLFW");
    glfwTerminate();

    spdlog::debug("Finished: Terminating Engine");
}

} // namespace Bob

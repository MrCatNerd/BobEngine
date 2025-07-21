#include "Window.h"

#include <spdlog/spdlog.h>

static void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
}

namespace Bob {

Window::Window(const std::string &name, int width, int height)
    : window(nullptr), name(name), width(width), height(height) {
    spdlog::debug("Initializing Window");

    spdlog::debug("Creating GLFWwindow");
    this->window = glfwCreateWindow(this->width, this->height,
                                    this->name.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    spdlog::debug("Initalizing GLAD");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("Failed to initialize GLAD");
        exit(-1);
    }

    spdlog::debug("Configuring OpenGL");
    glEnable(GL_DEPTH_TEST);

    spdlog::debug("Configuring viewport");
    glViewport(0, 0, this->width, this->height);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

Window::~Window(void) { spdlog::debug("Terminating Window"); }

} // namespace Bob

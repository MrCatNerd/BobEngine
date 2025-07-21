#include "BobEngine.h"

#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void GLAPIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id,
                                       GLenum severity, GLsizei length,
                                       const GLchar *message,
                                       const void *userParam) {
    (void)source;
    (void)type;
    (void)id;
    (void)length;
    (void)userParam;

    spdlog::error("OpenGL Debug: {:s}", message);
    if (severity == GL_DEBUG_SEVERITY_HIGH) {
        fprintf(stderr, "Aborting...\n");
        abort();
    }
}

static void glfwErrorCallback(int error, const char *description) {
    spdlog::error("GLFW Error ({:d}): {:s}\n", error, description);
}

namespace Bob {

Engine::Engine(void) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::debug("Initalizing Engine...");

    spdlog::debug("Setting GLFW error callback");
    glfwSetErrorCallback(glfwErrorCallback);

    spdlog::debug("Initalizing GLFW");
    if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW");
        exit(-1);
    }

    spdlog::debug("Configuring GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if TARGET_OS == MacOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    this->window = new Window("BobEngine", 1000, 1000);

    spdlog::debug("Initalizing GLAD");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("Failed to initialize GLAD");
        exit(-1);
    }

    this->window->configure();

    spdlog::debug("Loaded OpenGL Version: {}.{}", GLVersion.major,
                  GLVersion.minor);

    if (glfwExtensionSupported("GL_KHR_debug") && GLVersion.major >= 4 &&
        GLVersion.minor >= 3) {
        spdlog::debug("Setting GL debug callback");
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugCallback, nullptr);
    }

    spdlog::debug("Finished: Initalizing Engine");
}

Engine::~Engine(void) {
    spdlog::debug("Terminating Engine");

    delete this->window;

    spdlog::debug("Terminating GLFW");
    glfwTerminate();

    spdlog::debug("Finished: Terminating Engine");
}

} // namespace Bob

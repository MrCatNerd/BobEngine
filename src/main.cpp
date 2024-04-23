// Normal includes
#include <iostream>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Engine includes
#include "buffer.hpp"
#include "debug.hpp"
#include "shader.hpp"
#include "utils.hpp"

// prototypes
static inline void framebuffer_size_callback(GLFWwindow *window, int width,
                                             int height);

static inline void processInput(GLFWwindow *window);

// constants
static const unsigned int WINDOW_WIDTH = 720;
static const unsigned int WINDOW_HEIGHT = 600;
static const bool VSYNC = false;

int main(void) {
    LOG("[DEBUG] Initializing GLFW");
    if (!glfwInit()) {
        EngineError("[ERROR] Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    LOG("[DEBUG] Initializing window");
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "Hello World!", NULL, NULL);
    if (window == NULL) {
        EngineError("[ERROR] Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    LOG("[DEBUG] Initializing GLEW");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        EngineError("[ERROR] GLEW initialization failed: " +
                    std::string(reinterpret_cast<const char *>(
                        glewGetErrorString(err))));
    }

    LOG("[DEBUG] Setting stuff up")
    GLCALL(glfwSwapInterval((int)VSYNC)); // vsync
    GLCALL(glfwSetFramebufferSizeCallback(window, framebuffer_size_callback));

    LOG("[DEBUG] Initialized OpenGL\n[DEBUG] OpenGL Version: "
        << glGetString(GL_VERSION));

#ifdef _DEBUG

    int nrAttributes;
    GLCALL(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes));
    LOG("[DEBUG] Maximum number of vertex attributes supported: "
        << nrAttributes)

#endif

    // initialize general stuff

    float vertices[] = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    Buffer vboffa(GL_ARRAY_BUFFER, sizeof(vertices), vertices);
    Buffer eboffa(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices);
    vboffa.setupVertexAttribPointer(3, GL_FLOAT, GL_FALSE, (void *)(0));

    const std::string vert_src = GetFile("res/shaders/vert.glsl");
    const std::string frag_src = GetFile("res/shaders/frag.glsl");

    Shader shader(vert_src, frag_src);

    // engine go bRRRRRRRRRRRRRRRRRRRRRR

    LOG("[DEBUG] starting main loop");

    float last_time = glfwGetTime();
    float deltaTime;

    while (!glfwWindowShouldClose(window)) {

        // Compute delta time
        deltaTime = glfwGetTime() - last_time;
        last_time = glfwGetTime();

        // Lets color up that boi
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Proccess input
        processInput(window);

        shader.bind();
        glBindVertexArray(VAO);
        eboffa.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Flippety flip the buffers
        GLCALL(glfwSwapBuffers(window));

        GLCALL(glfwPollEvents());
    }

    LOG("[DEBUG] mission failed successfully, shutting down...");
    // terminate opengl stuff
    glfwTerminate();

    return 0;
}

static inline void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) ==
        GLFW_PRESS) { // Press escape to exit program
        GLCALL(glfwSetWindowShouldClose(window, true));
    }

    static bool lock = 0, wf_mode = 0;
    if (!glfwGetKey(window, GLFW_KEY_W)) { // press W to toggle wireframe mode
        lock = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_W) && lock == 0) {
        GLCALL(glPolygonMode(GL_FRONT_AND_BACK,
                             (wf_mode = 1 - wf_mode) ? GL_LINE : GL_FILL));
        LOG("[DEBUG] wireframe mode toggled: " << ((wf_mode == true) ? "on"
                                                                     : "off"));
        lock = 1;
    }
}

static inline void framebuffer_size_callback(GLFWwindow *window, int width,
                                             int height) {
    GLCALL(glViewport(0, 0, width, height));
}

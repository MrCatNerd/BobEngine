// normal stuff
#include <iostream>
#include <string>

// OpenGL stuff
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Engine stuff

#include "buffer.hpp"
#include "buffer_array.hpp"
#include "shader.hpp"

#include "debug.hpp"
#include "utils.hpp"

// Prototypes
static inline void framebuffer_size_callback(GLFWwindow *window, int width,
                                             int height);

static inline void processInput(GLFWwindow *window);

// TODO: settings from a json file or smh
// Settings
static const unsigned int SCREEN_WIDTH = 800;
static const unsigned int SCREEN_HEIGHT = 600;
static const bool VSYNC = false; // set to true to enable VSync
// #define __MAC__                  // if you are on MacOS uncomment this line

int main(void) {
    // Initialize and configure glfw
    if (!glfwInit()) {
        glfwError("Failed to initialize GLFW!");
        return -1;
    }

    GLCALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
    GLCALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCALL(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

#ifdef __MAC__
    GLCALL(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE));
#endif

    // Glfw window creation
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
                                          "BobEngine", nullptr, nullptr);
    if (window == nullptr) {
        glfwError("Failed to create GLFW window");
        return -1;
    }

    GLCALL(glfwMakeContextCurrent(window));
    GLCALL(glfwSetFramebufferSizeCallback(window, framebuffer_size_callback));
    GLCALL(glfwSwapInterval((int)VSYNC)); // vsync

    // Glew: load all OpenGL function pointers
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW initialization failed: " << glewGetErrorString(err)
                  << std::endl;
        return -1;
    }

    LOG("Initialized OpenGL\nOpenGL Version: " << glGetString(GL_VERSION));

#ifdef __DEBUG__
    int nrAttributes;
    GLCALL(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes));
    LOG("Maximum number of vertex attributes supported: " << nrAttributes)

    LOG("Starting to generate the lil triangle");

    // Build and compile shader program
    LOG("Creating a shader program");
#endif
    /* float vertices[] = {
        //    Position     |      Color
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // top right
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.8f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f, // top left
    }; */

    float vertices[] = {
        //    Position
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // First triangle (top-left, bottom-left, bottom-right)
        1, 2, 3  // Second triangle (top-left, bottom-right, top-right)
    };

    LOG("Creating VBOs, VAOs and EBOs");

    // IDs
    unsigned int VAO;

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    BufferArray vao;

    vao.bind();

    Buffer vbo(GL_ARRAY_BUFFER);
    Buffer ebo(GL_ELEMENT_ARRAY_BUFFER);

    // VBO
    vbo.bind();
    vbo.data(vertices, sizeof(vertices));

    vbo.setupVertexAttribPointer(3, GL_FLOAT, GL_FALSE, (void *)0);
    // vbo.setupVertexAttribPointer(3, GL_FLOAT, GL_FALSE,
    //                              (void *)(3 * sizeof(float)));

    // EBO
    ebo.bind();
    ebo.data(indices, sizeof(indices));

    // Shaders
    std::string vertexShaderSource = GetFile("res/shaders/vert.glsl");

    std::string fragmentShaderSource = GetFile("res/shaders/frag.glsl");

    Shader shader(vertexShaderSource, fragmentShaderSource);

    shader.bind();
    // shader.set_Uniform4f("u_Time", 0.0, 0.0, 0.0, 0.0);

    LOG("Finished generating our lil triangle");

    // Clear stuff
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    vbo.unbind();
    ebo.unbind();
    BufferArray::unbind();
    GLCALL(glBindVertexArray(0));
    Shader::unbind();

    LOG("Starting main loop...");

    float r = 1.0;
    float increment = 0.05;
    float lastTime = glfwGetTime();
    float deltaTime;

    while (!glfwWindowShouldClose(window)) {
        // Get delta time
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        // Proccess input
        processInput(window);

        // Clear the frame buffer
        GLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        // Bind a shader
        shader.bind();

        // Set the uniform
        // shader.st_Uniform4f("u_Time", r, r, r, r);

        // Bind VAO and EBO
        vao.bind();
        ebo.bind();

        // Draw
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // Change r by time and stuff
        if (r > 2) {
            increment = -0.05 * deltaTime * 60;
        } else if (r < 0) {
            increment = 0.05 * deltaTime * 60;
        }

        r += increment;

        glfwSwapBuffers(window); // Swap frame buffers
        glfwPollEvents();        // Poll for events (amazing explanation)
    }

    LOG("Cleaning up...");

    glfwTerminate();
    LOG("GLFW was terminated successfully... mission failed successfully!");

    return 0;
}

static inline void framebuffer_size_callback(GLFWwindow *window, int width,
                                             int height) {
    glViewport(0, 0, width, height);
}

static inline void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) ==
        GLFW_PRESS) // Press escape to exit program
        glfwSetWindowShouldClose(window, true);

    static bool lock = 0, wf_mode = 0;
    if (!glfwGetKey(window, GLFW_KEY_W)) { // press W to toggle wireframe mode
        lock = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_W) && lock == 0) {
        glPolygonMode(GL_FRONT_AND_BACK,
                      (wf_mode = 1 - wf_mode) ? GL_LINE : GL_FILL);
        LOG("Line Mode: "
            << (bool)(wf_mode =
                          1 - wf_mode)); // FIXME: yea no worky only prints 0
        lock = 1;
    }
}

// TODO:
// sorted mostly by priority
// --------------------------
// [ ] shader abstraction
// [ ] small cleanup
// [ ] better errors
// --------- extras ---------
// [ ] cool shader
// [ ] find out why program fails when i don't bind the EBO every frame (the VAO
// should be doing that automatically)
// --------- done ---------
// [x] CMAKE
// [x] include folder without clangd lsp freaking out
// [x] fix stupid shader errors
// [x] file reading (for shaders)
// [x] deltaTime
// [x] vsync support (literally 2 lines of code)

// Normal includes
#include <iostream>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Engine includes
#include "buffer.hpp"
#include "debug.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "utils.hpp"
#include "camera.hpp"
// #include "texture.hpp"

// prototypes
static inline void framebuffer_size_callback(GLFWwindow *window, int width,
                                             int height);
static inline void scroll_callback(GLFWwindow *window, double xoffset,
                                   double yoffset);

static inline void processInput(GLFWwindow *window);

// constants
static const unsigned int WINDOW_WIDTH = 720;
static const unsigned int WINDOW_HEIGHT = 600;
static const bool VSYNC = false;

// stupid callback scrolling stuff (thank you openGL -_-)
// btw i do it so i can access the camera thingy :(
float scroll_offset_x = 0.0f;
float scroll_offset_y = 0.0f;

int main(void) {
    LOG("[DEBUG] Initializing GLFW");
    if (!glfwInit()) {
        EngineError("[ERROR] Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _MACOS // if macos
    LOG("[DEBUG] MacOS detected, enabling forward compatibility");
    GLCALL(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE));
#endif

    LOG("[DEBUG] Initializing window");
    GLFWwindow *window =
        glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "BobEngine", NULL, NULL);
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

    LOG("[DEBUG] Setting callback functions")
    GLCALL(glfwSetFramebufferSizeCallback(window, framebuffer_size_callback));
    GLCALL(glfwSetScrollCallback(window, scroll_callback));

    LOG("[DEBUG] Initialized OpenGL\n[DEBUG] OpenGL Version: "
        << glGetString(GL_VERSION));

#ifdef _DEBUG

    int nrAttributes;
    GLCALL(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes));
    LOG("[DEBUG] Maximum number of vertex attributes supported: "
        << nrAttributes)

#endif

    LOG("[DEBUG] Enabling depth test");
    glEnable(GL_DEPTH_TEST);

    // LOG("[DEBUG] Enabling blend");
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize general stuff

    /* float vertices[] = {
        // positions  // colors         // texture coords
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    }; */

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.5f,  -0.5f,
        -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 0.0f,
        0.0f,  -1.0f, 1.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
        1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
        0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,
        0.0f,  1.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,
        -0.5f, -1.0f, 0.0f,  0.0f,  1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f,
        0.0f,  0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
        0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
        -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,
        0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
        -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
        -1.0f, 0.0f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
        1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,
        -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,
        1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f};

    // Generate VBO
    Buffer VBOffa(GL_ARRAY_BUFFER);
    VBOffa.bind();
    VBOffa.data(sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Generate EBO
    // Buffer EBOffa(GL_ELEMENT_ARRAY_BUFFER);
    // EBOffa.bind();
    // EBOffa.data(sizeof(indices), indices, GL_STATIC_DRAW);

    // VAOs
    unsigned int cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    VBOffa.bind();
    VBOffa.setupVertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                                    (void *)(0), false);
    VBOffa.setupVertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                                    (void *)(3 * sizeof(float)), false);
    VBOffa.setupVertexAttribPointer(2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                                    (void *)(6 * sizeof(float)), false);

    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    VBOffa.setupVertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                                    (void *)(0), true);

    // Light stuff
    glm::vec3 lightPos(1.2f, 1.0f, 0.0f);

    // Camera
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f));

    // Shaders
    Shader light_shader(GetFile("res/shaders/vertex/light_vert.glsl"),
                        GetFile("res/shaders/fragment/light_shader.glsl"));

    Shader object_shader(GetFile("res/shaders/vertex/object_vert.glsl"),
                         GetFile("res/shaders/fragment/object_shader.glsl"));

    // Texture for object shader
    Texture container_textures(
        2,
        {"res/textures/container.png",
         // {"res/speculars/lighting_maps_specular_color.png" }
         {"res/speculars/container_specular.png"}},
        true);
    // no alpha so new texture thingy
    Texture container_emission(1, {"res/emissions/matrix_emission.jpg"}, false);

    // Set sampler for texture
    object_shader.bind();
    object_shader.set_Uniform1i("material.diffuse", 0);
    object_shader.set_Uniform1i("material.specular", 1);
    object_shader.set_Uniform1i("material.emission", 2);
    object_shader.set_Uniform1f("material.shininess", 32.0f);

    // engine go bRRRRRRRRRRRRRRRRRRRRRR

    float last_time = glfwGetTime();
    float deltaTime = 0.0f;

    LOG("[DEBUG] starting main loop");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    LOG("[DEBUG] main loop started");
    while (!glfwWindowShouldClose(window)) {
        // Compute delta time
        deltaTime = glfwGetTime() - last_time;
        last_time = glfwGetTime();

        // Lets color up that boi
        GLCALL(glClearColor(0.19215686274509805, 0.1843137254901961f,
                            0.21176470588235294f, 1.0f));

        GLCALL(glClear(GL_COLOR_BUFFER_BIT |
                       GL_DEPTH_BUFFER_BIT)); // clear color and z buffer

        // Proccess general input
        processInput(window);

        // Camera
        camera.inputs(window, deltaTime); // Handle camera inputs
        camera.proccess_zoom(scroll_offset_y * deltaTime * 3000);

        // get MVP
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.get_view_matrix(45.0f, 0.1f, 100.0f);
        glm::mat4 projection = camera.get_projection_matrix();

        // object
        object_shader.bind();
        object_shader.set_UniformMatrix4fv("model", model);
        object_shader.set_UniformMatrix4fv("view", view);
        object_shader.set_UniformMatrix4fv("projection", projection);

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(model * view));
        object_shader.set_UniformMatrix3fv("normalMatrix", normalMatrix);

        lightPos.x = cos(glfwGetTime()) * 2.0f;
        lightPos.y = (sin(glfwGetTime()) + cos(glfwGetTime())) * 2.0f;
        lightPos.z = cos(glfwGetTime()) * 2.0f;

        object_shader.set_Uniform3f("lightPos", lightPos.x, lightPos.y,
                                    lightPos.z);

        object_shader.set_Uniform3f("light.diffuse", 1.0f, 1.0f, 1.0f);
        object_shader.set_Uniform3f("light.ambient", 0.5f, 0.5f, 0.5f);
        object_shader.set_Uniform3f("light.specular", 1.0f, 1.0f, 1.0f);

        container_textures.bind();
        container_emission.bind();

        GLCALL(glBindVertexArray(cubeVAO));
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, 36));

        // light
        light_shader.bind();
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        light_shader.set_UniformMatrix4fv("model", model);
        light_shader.set_UniformMatrix4fv("view", view);
        light_shader.set_UniformMatrix4fv("projection", projection);
        light_shader.set_Uniform3f("lightColor", 1.0f, 1.0f, 1.0f);

        GLCALL(glBindVertexArray(lightCubeVAO));
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, 36));

        // OpenGL bein' evil :(
        // must zero this before glfwSwapBuffers cuz event stuff
        scroll_offset_x = 0.0f;
        scroll_offset_y = 0.0f;

        // Flippety flip the buffers
        GLCALL(glfwSwapBuffers(window));

        GLCALL(glfwPollEvents());
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);

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
    if (!glfwGetKey(window,
                    GLFW_KEY_Q)) { // press W to toggle wireframe mode
        lock = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) && lock == 0) {
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

void scroll_callback(GLFWwindow *window, double offset_x, double offset_y) {
    scroll_offset_x = static_cast<float>(offset_x);
    scroll_offset_y = static_cast<float>(offset_y);
}

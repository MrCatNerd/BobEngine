#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Bob {

class Window {
    public:
        Window(const std::string &name, int width, int height);
        ~Window(void);

        bool shouldClose(void) { return glfwWindowShouldClose(this->window); }

        void configure(void) const;

        void clear(const float r, const float g, const float b, const float a) {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT);
        }

        void flip(void) { glfwSwapBuffers(this->window); };

        void poll(void) { glfwPollEvents(); };

    private:
        GLFWwindow *window;
        const std::string name;
        int width, height;
};

}; // namespace Bob

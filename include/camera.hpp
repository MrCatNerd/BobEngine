#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
    public:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

        const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        // euler angles
        float yaw = -90.0f;
        float pitch = 0.0f;
        float roll = 0.0f; // not doing anything yet

        // settings
        float sensitivity = 0.209f;
        float fov = 90.0f;

        unsigned int width, height;

        Camera(unsigned int width, unsigned int height, glm::vec3 position);
        ~Camera() = default;

        void proccess_zoom(float offset_y);
        void inputs(GLFWwindow *window, float deltaTime);
        glm::mat4 get_view_matrix(float FOVdeg, float near_plane,
                                  float far_plane);
        glm::mat4 get_projection_matrix();
};

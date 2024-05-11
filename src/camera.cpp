#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#include "camera.hpp"

Camera::Camera(unsigned int width, unsigned int height, glm::vec3 position)
    : position(position), width(width), height(height) {}

void Camera::proccess_zoom(float offset_y) {
    this->fov -= offset_y;

    if (this->fov < 1.0f)
        this->fov = 1.0f;
    if (this->fov > 90.0f)
        this->fov = 90.0f;
}

glm::mat4 Camera::get_view_matrix(float FOVdeg, float near_plane,
                                  float far_plane) {
    // View matrix
    // note that we're translating the scene in the reverse direction of where
    // we want to move
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

glm::mat4 Camera::get_projection_matrix() {
    // Perspective matrix
    return glm::perspective(glm::radians(this->fov),
                            (float)this->width / (float)this->height, 0.1f,
                            100.0f);
}

void Camera::inputs(GLFWwindow *window, float deltaTime) {
    float cameraSpeed = 0.05f * deltaTime * 60; // adjust accordingly

    // keyboard controls
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        // this->position += cameraSpeed * this->front;
        this->position +=
            cameraSpeed *
            glm::normalize(glm::vec3(this->front.x, 0.0, this->front.z));
    // this->position +=
    //     cameraSpeed * glm::normalize(glm::cross(
    // this->up, glm::cross(this->front, this->up)));

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        // this->position -= cameraSpeed * this->front;
        this->position -=
            cameraSpeed *
            glm::normalize(glm::vec3(this->front.x, 0.0, this->front.z));

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->position -=
            cameraSpeed * glm::normalize(glm::cross(this->front, this->up));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        this->position +=
            cameraSpeed * glm::normalize(glm::cross(this->front, this->up));
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        this->position += this->up * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        this->position -= this->up * cameraSpeed;

    // mouse controls
    static bool was_normal_mouse = true; // so the mouse won't jump around

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) ==
        GLFW_PRESS) { // on right click
        glfwSetInputMode(window, GLFW_CURSOR,
                         GLFW_CURSOR_DISABLED); // hide and capture (lock) the
                                                // mouse (ya cant see it)

        static double lastX = (double)this->width / 2;
        static double lastY = (double)this->height / 2;

        // get mouse position
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        if (was_normal_mouse) // initially set to true
        {
            lastX = mouseX;
            lastY = mouseY;
            was_normal_mouse = false;
        }

        double offsetX = (mouseX - lastX) * this->sensitivity;
        double offsetY = (lastY - mouseY) * this->sensitivity;
        lastX = mouseX;
        lastY = mouseY;

        yaw += offsetX * sensitivity;
        pitch += offsetY * sensitivity;

        // no flippin' today boiii
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        // Euler angles
        // todo: mess around with roll
        glm::vec3 direction;
        direction.x =
            cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        direction.y = sin(glm::radians(this->pitch));
        direction.z =
            sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        this->front = glm::normalize(direction);
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) ==
               GLFW_RELEASE) { // on right click release
        glfwSetInputMode(window, GLFW_CURSOR,
                         GLFW_CURSOR_NORMAL); // set cursor to normal mode
                                              // thingy (dont hide it)
        was_normal_mouse = true;
    }
}

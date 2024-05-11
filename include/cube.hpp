#pragma once

// TODO: delete this useless backup file
namespace Cube {
float vertices[] = {
    -0.5, -0.5, 0.5,  // vertex 0
    -0.5, -0.5, -0.5, // vertex 1
    0.5,  -0.5, -0.5, // vertex 2
    0.5,  -0.5, 0.5,  // vertex 3
    0.5,  0.5,  -0.5, // vertex 4
    -0.5, 0.5,  -0.5, // vertex 5
    -0.5, 0.5,  0.5,  // vertex 6
    0.5,  0.5,  0.5,  // vertex 7
};

unsigned int indices[] = {
    // I had to make this EBO by hand :(((((
    //
    // note that we start from 0!

    // square 1
    0, 1, 2, // triangle 1
    0, 2, 3, // triangle 2

    // square 2
    0, 3, 7, // triangle 3
    0, 6, 7, // triangle 4

    // square 3
    2, 3, 7, // triangle 5
    2, 4, 7, // triangle 6

    // square 4
    1, 0, 6, // triangle 7
    1, 5, 6, // triangle 8

    // square 5
    1, 5, 4, // triangle 9
    1, 2, 4, // triangle 10

    // square 6
    4, 7, 6, // triangle 11
    4, 5, 6, // triangle 12
};
// EBOffa.bind();
// GLCALL(glDrawElements(GL_TRIANGLES,
//                       sizeof(indices) / sizeof(unsigned int),
//                       GL_UNSIGNED_INT, 0));
} // namespace Cube

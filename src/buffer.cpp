#include <iostream>

#include <GL/glew.h>

#include "include/buffer.hpp"
#include "include/debug.hpp"

Buffer::Buffer(int type) : m_type(type) {
    GLCALL(glGenBuffers(1, &m_id));
    LOG("Generated buffer " << m_id);
}

void Buffer::bind() const { GLCALL(glBindBuffer(m_type, m_id)); }
void Buffer::unbind() const { GLCALL(glBindBuffer(m_type, 0)); }

void Buffer::data(const void *data, int size) const {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data,
                 GL_STATIC_DRAW); // loads data into buffer
}

unsigned int Buffer::get_id() const { return m_id; }

void Buffer::setupVertexAttribPointer(int size, unsigned int type,
                                      unsigned int normalized,
                                      const void *pointer,
                                      unsigned int jumps) const {
    static unsigned int index = 0;
    jumps += 1;

    int maxVertexAttribs = 1;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);

    // Check if index exceeds the maximum vertex attributes
    if (index >= maxVertexAttribs) {
        // Handle error: Index exceeds maximum vertex attributes
        std::cerr << "Error: Exceeded maximum vertex attributes\n";
        return;
    }

    // Get size by type
    unsigned int type_size = 0;

    switch (type) {
    case GL_FLOAT:
        type_size = sizeof(float);
        break;
    case GL_INT:
        type_size = sizeof(int);
        break;
    case GL_UNSIGNED_INT:
        type_size = sizeof(unsigned int);
        break;
    case GL_UNSIGNED_BYTE:
        type_size = sizeof(unsigned char);
        break;
    default:
        std::cerr << "Error: Invalid type (" << __FILE__ << ":" << __LINE__
                  << ")" << std::endl;
        break;
    }

    int stride = (jumps * size) * type_size;

    // Bind the buffer
    bind();

    // Set up attribute pointer
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);

    // Increment index for the next attribute
    index++;

    // Reset index if it exceeds the maximum vertex attributes
    if (index >= maxVertexAttribs) {
        index = 0;
    }
}

Buffer::~Buffer() { GLCALL(glDeleteBuffers(1, &m_id)); }

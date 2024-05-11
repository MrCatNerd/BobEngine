#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "debug.hpp"
#include "buffer.hpp"

Buffer::Buffer(int buffer_type) : m_buffer_type(buffer_type) {
    GLCALL(glGenBuffers(1, &this->m_id));
    this->bind();
    LOG("[DEBUG] Generated buffer #" << this->m_id);
}

void Buffer::data(unsigned int size, void *data, unsigned int usage) const {
    GLCALL(glBufferData(this->m_buffer_type, size, data, usage));
}

Buffer::~Buffer() { GLCALL(glDeleteBuffers(1, &this->m_id)); }

void Buffer::setupVertexAttribPointer(int size, unsigned int type,
                                      unsigned char normalized, int stride,
                                      const void *pointer,
                                      bool reset_layout) const {
    static unsigned int layout_index =
        0; // if you change it to 1 the world ends btw

    if (reset_layout) {
        layout_index = 0;
    } else {
    }

    GLCALL(glEnableVertexAttribArray(layout_index));
    GLCALL(glVertexAttribPointer(layout_index, size, type, normalized, stride,
                                 pointer));

    layout_index++;
}

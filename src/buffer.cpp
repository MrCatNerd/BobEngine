#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "debug.hpp"
#include "utils.hpp"
#include "buffer.hpp"

Buffer::Buffer(int buffer_type, unsigned int size, void *data)
    : m_buffer_type(buffer_type) {
    GLCALL(glGenBuffers(1, &this->m_id));
    this->bind();
    GLCALL(glBufferData(this->m_buffer_type, size, data, GL_STATIC_DRAW));

    LOG("[DEBUG] Generated buffer " << this->m_id);
}

Buffer::~Buffer() { GLCALL(glDeleteBuffers(1, &this->m_id)); }

void Buffer::setupVertexAttribPointer(int size, unsigned int type,
                                      unsigned char normalized,
                                      const void *pointer) const {
    static unsigned int layout_index = 0;

    // calculate stride
    unsigned short type_size = get_gl_type_size(type);
    int stride = size * type_size;

    GLCALL(glVertexAttribPointer(layout_index, size, type, normalized,
                                 3 * sizeof(float), pointer));
    GLCALL(glEnableVertexAttribArray(layout_index));

    layout_index++;
}

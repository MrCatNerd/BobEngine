#include <GL/glew.h>

#include "buffer.hpp"
#include "debug.hpp"
#include "utils.hpp"

Buffer::Buffer(int type) : m_type(type) {
    GLCALL(glGenBuffers(1, &m_id));
    LOG("Generated buffer " << m_id);

    bind();
}

void Buffer::bind() const { GLCALL(glBindBuffer(m_type, m_id)); }
void Buffer::unbind() const { GLCALL(glBindBuffer(m_type, 0)); }

Buffer::~Buffer() { GLCALL(glDeleteBuffers(1, &m_id)); }

void Buffer::setupVertexAttribPointer(int size, unsigned int type,
                                      unsigned char normalized,
                                      const void *pointer) const {

    static unsigned int index = 1;

    // bind
    this->bind();

    // calculate stride
    unsigned short type_size = get_gl_type_size(type);
    int stride = size * type_size;

    // stride = 0;                     // 0 if tightly packed

    // calculate pointer

    // do the other stuff
    GLCALL(glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer));
    GLCALL(glEnableVertexAttribArray(index));

    ++index;
}

void Buffer::data(const void *data, int size) const {
    this->bind();

    glBufferData(
        this->m_type, size, data,
        GL_STATIC_DRAW); // TODO: allow more types than static draw thingy
}

#include <GL/glew.h>

#include "buffer.hpp"
#include "debug.hpp"

Buffer::Buffer(int type) {
    LOG("Generated buffer " << m_id);
    GLCALL(glGenBuffers(1, &m_id));

    bind();
}

unsigned int Buffer::get_id() const { return m_id; }
void Buffer::bind() const { GLCALL(glBindBuffer(m_type, m_id)); }
void Buffer::unbind() const { GLCALL(glBindBuffer(m_type, 0)); }

Buffer::~Buffer() { GLCALL(glDeleteBuffers(1, &m_id)); }

void Buffer::setupVertexAttribPointer(int size, unsigned int type,
                                      unsigned int normalized,
                                      const void *pointer,
                                      unsigned int jumps) const {}
void Buffer::data(const void *data, int size) const {}

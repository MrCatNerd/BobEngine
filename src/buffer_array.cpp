#include <GL/glew.h>

#include "include/buffer_array.hpp"

BufferArray::BufferArray() { glGenVertexArrays(1, &m_id); }

void BufferArray::bind() const { glBindVertexArray(m_id); }

void BufferArray::unbind() const { glBindVertexArray(0); }

BufferArray::~BufferArray() { glDeleteVertexArrays(1, &m_id); }

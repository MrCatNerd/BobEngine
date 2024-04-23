#pragma once

#include <GL/glew.h>

#include "debug.hpp"

class Buffer {
    private:
        unsigned int m_id = 0;
        int m_buffer_type;

    public:
        Buffer(int buffer_type, unsigned int size, void *data);
        ~Buffer();

        inline void bind() const {
            GLCALL(glBindBuffer(this->m_buffer_type, this->m_id));
        }
        inline void unbind() { GLCALL(glBindBuffer(this->m_buffer_type, 0)); }

        void setupVertexAttribPointer(int size, unsigned int type,
                                      unsigned char normalized,
                                      const void *pointer) const;
};

#pragma once

#include <GL/glew.h>

#include "debug.hpp"

class Buffer {
    private:
        unsigned int m_id = 0;
        int m_buffer_type;

    public:
        Buffer(int buffer_type);
        ~Buffer();

        void data(unsigned int size, void *data, unsigned int usage) const;

        void setupVertexAttribPointer(int size, unsigned int type,
                                      unsigned char normalized, int stride,
                                      const void *pointer) const;

        void setupVertexAttribPointer(int size, unsigned int type,
                                      unsigned char normalized, int stride,
                                      const void *pointer,
                                      bool reset_layout) const;

        inline void bind() const {
            GLCALL(glBindBuffer(this->m_buffer_type, this->m_id));
        }

        inline void unbind() const {
            GLCALL(glBindBuffer(this->m_buffer_type, 0));
        }
};

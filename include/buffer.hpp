#pragma once

class Buffer {
    private:
        unsigned int m_id = 0;
        unsigned int m_type = 0;

    public:
        Buffer(int type);

        void bind() const;
        void unbind() const;
        void data(const void *data, int size) const;
        void setupVertexAttribPointer(int size, unsigned int type,
                                      unsigned int normalized,
                                      const void *pointer,
                                      unsigned int jumps) const;

        unsigned int get_id() const;

        ~Buffer();
};

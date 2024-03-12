#pragma once

class BufferArray {
    private:
        unsigned int m_id = 0;

    public:
        BufferArray();

        void bind() const;
        void unbind() const;

        unsigned int get_id() const;

        ~BufferArray();
};

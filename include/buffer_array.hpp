#pragma once

class BufferArray {
    private:
        unsigned int m_id = 0;

    public:
        BufferArray();

        void bind() const;
        static void unbind();

        unsigned int get_id() const;

        ~BufferArray();
};

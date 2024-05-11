#pragma once

#include <string>
#include <vector>

class Texture {
    private:
        unsigned int m_texture_count;
        unsigned int *m_textures;

    public:
        Texture(unsigned int texture_count,
                const std::vector<std::string> &texture_paths, bool alhpa);
        ~Texture();

        const void bind() const;
};

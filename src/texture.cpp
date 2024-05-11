#include <GL/glew.h>
#include <GLFW/glfw3.h>

// todo: try assimp
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.hpp"
#include "debug.hpp"

static void create_texture(unsigned int texture_id, const char *texture_path,
                           bool alhpa);

Texture::Texture(unsigned int texture_count,
                 const std::vector<std::string> &texture_paths, bool alhpa)
    : m_texture_count(texture_count) {
    // Texture settings (todo: find a better way than this)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    // allocate memeroy for the texture ids (to allow multiple textures)
    this->m_textures = new unsigned int[texture_count];
    GLCALL(glGenTextures(texture_count, m_textures));

    for (unsigned int i = 0; i < texture_count; i++) {
        create_texture(m_textures[i], texture_paths[i].c_str(), alhpa);
        LOG("[DEBUG] Created texture: " << this->m_textures[i]);
    }
}

const void Texture::bind() const {
    for (unsigned int i = 0; i < this->m_texture_count; i++)
        glBindTexture(GL_TEXTURE_2D, this->m_textures[i]);
}

Texture::~Texture() {
    glDeleteTextures(this->m_texture_count, this->m_textures);
    delete this->m_textures;
}

static void create_texture(unsigned int texture_id, const char *texture_path,
                           bool alpha) {
    static unsigned int iteration = 0;

    GLCALL(glActiveTexture(
        GL_TEXTURE0 +
        iteration)); // activate the texture unit first before binding texture
    GLCALL(glBindTexture(GL_TEXTURE_2D, texture_id));

    int width, height, nrChannels;
    unsigned char *data =
        stbi_load(texture_path, &width, &height, &nrChannels, 0);

    if (data) {
        // todo: try distance lod stuff
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                     GL_RGB + static_cast<int>(alpha), GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        LOG("[ERROR] Something went wrong with loading your lil texture");
    }

    stbi_image_free(data);
    ++iteration; // hehehehe
}

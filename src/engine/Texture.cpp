#include "Texture.h"

Texture::Texture(GLuint textureID) : textureID(textureID) { }
/*
Texture::Texture(const Texture& other) {
    *this = other;
}
*/
void Texture::bind(GLenum texture) {
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
/*
Texture& Texture::operator=(const Texture& other) {
    if (this != &other) {
        textureID = other.textureID;
    }
    return *this;
}
*/
Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}


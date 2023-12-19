#pragma once

#include "Global.h"

class Texture {
private:
public:
    GLuint textureID;
    
    Texture() = default;
    Texture(GLuint textureID);
    //Texture(const Texture& other);

    void bind(GLenum texture);
    void unbind();

   // Texture& operator=(const Texture& other);
    ~Texture();
};



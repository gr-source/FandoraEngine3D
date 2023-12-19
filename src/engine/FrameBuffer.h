#pragma once

#include "Global.h"

class FrameBuffer {
public:
    FrameBuffer();
    ~FrameBuffer();

    void bind();
    void unbind();
    void resize(float width, float height);

    GLuint textureID;
    GLuint postTextureID;
private:
    GLuint postFBO;
    GLuint FBO;
    GLuint RBO;
};





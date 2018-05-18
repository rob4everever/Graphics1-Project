/*
- Texture.cpp
-
- Author: 100086865
-
- Source file for Texture.hpp, contains function definitions.
*/

#include "Texture.hpp"

Texture::Texture() : width(0), height(0), internal_format(GL_RGB), image_format(GL_RGB), wrap_S(GL_REPEAT), wrap_T(GL_REPEAT), filter_min(GL_LINEAR), filter_max(GL_LINEAR) {
    glGenTextures(1, &this->ID);
}

void Texture::generate(GLuint width, GLuint height, unsigned char* data) {

    this->width = width;
    this->height = height;

    //Create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0, this->image_format, GL_UNSIGNED_BYTE, data);

    //Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);

    //Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
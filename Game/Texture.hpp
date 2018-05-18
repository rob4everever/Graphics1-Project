/*
- Texture.hpp
-
- Author: 100086865
-
- Class that represents a generic texture. It creates,
- configures and applies a texture from an image source
- Provides functionality for easy management.
*/

#pragma once

#include <glad\glad.h>

class Texture {

public:
    //Texture ID    
    GLuint ID;

    //Texture image dimensions
    GLuint width, height;

    //Format of texture object                  
    GLuint internal_format;

    //Format of loaded image
    GLuint image_format;

    // Texture configuration
    GLuint wrap_S;          // Wrapping mode on S axis
    GLuint wrap_T;          // Wrapping mode on T axis
    GLuint filter_min;      // Filtering mode if texture pixels < screen pixels
    GLuint filter_max;      // Filtering mode if texture pixels > screen pixels

    /*
    - Texture constructor
    */
    Texture();

    /*
    - Generates texture from image data
    - @param: Texture width
    - @param: Texture height
    - @param: Image data
    */
    void generate(GLuint width, GLuint height, unsigned char* data);

    /*
    - Binds the texture as the current active texture object (GL_TEXTURE_2D))
    */
    void bind() const;
};
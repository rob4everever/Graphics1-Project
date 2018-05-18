/*
- ResourceLoader.hpp
-
- Author: 100086865
-
- Source file for ResourceLoader.hpp, contains function definitions.
*/

#include <SOIL\SOIL.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include "ResourceLoader.hpp"

//Instantiate static variables
std::map<std::string, Texture> ResourceLoader::textures;
std::map<std::string, Shader> ResourceLoader::shaders;

Shader ResourceLoader::loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name) {
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaders[name];
}

Shader ResourceLoader::getShader(std::string name) {
    return shaders[name];
}

Texture ResourceLoader::loadTexture(const GLchar *file, GLboolean alpha, std::string name) {
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

Texture ResourceLoader::getTexture(std::string name) {
    return textures[name];
}

void ResourceLoader::clear() {

    //Delete all shaders	
    for (auto iterator : shaders) {
        glDeleteProgram(iterator.second.ID);
    }

    //Delete all textures
    for (auto iterator : textures) {
        glDeleteTextures(1, &iterator.second.ID);
    }
}

Shader ResourceLoader::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile) {

    //Get shader source code
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try {

        //Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        //Read into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        //Close
        vertexShaderFile.close();
        fragmentShaderFile.close();

        //Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        //Load geometry shader if present
        if (gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();

    //Create shader object from source code
    Shader shader;

    shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture ResourceLoader::loadTextureFromFile(const GLchar *file, GLboolean alpha) {

    //Create Texture object
    Texture texture;

    if (alpha) {
        texture.internal_format = GL_RGBA;
        texture.image_format = GL_RGBA;
    }

    //Load image
    int width, height;
    unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.image_format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

    //Generate texture
    texture.generate(width, height, image);

    //Free image data
    SOIL_free_image_data(image);
    return texture;
}
/*
- ResourceLoader.hpp
-
- Author: 100086865
-
- Singleton class that hosts functions to load textures and shaders.
- Each texture/shader is stored for future use.
*/

#pragma once

#include <glad\glad.h>

#include <map>
#include <string>

#include "Texture.hpp"
#include "Shader.hpp"

class ResourceLoader {

public:

    //Shader and texture storage
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture> textures;

    /*
    - Loads (and generates) a shader program from shader source code
    - @param: Vertex shader source
    - @param: Fragment shader source
    - @param: Geometry shader source (optional)
    - @param: Shader program name
    - @return: Shader program
    */
    static Shader loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);

    /*
    - Gets a stored shader program
    - @param: Shader program name
    - @return: Shader program
    */
    static Shader getShader(std::string name);

    /*
    - Loads (and generates) a texture from file
    - @param: Texture file
    - @param: Alpha boolean
    - @param: Texture name
    - @return: Texture
    */
    static Texture loadTexture(const GLchar *file, GLboolean alpha, std::string name);

    /*
    - Gets a stored texture
    - @param: Texture name
    - @return: Texture
    */
    static Texture getTexture(std::string name);

    /*
    - Deallocates loaded resources
    */
    static void clear();

private:

    /*
    - Private constructor
    */
    ResourceLoader() { }

    /*
    - Loads and generates a shader from file
    - @param: Vertex shader file
    - @param: Fragment shader file
    - @param: Geometry shader file (optional)
    - @return: Shader program
    */
    static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);

    /*
    - Loads a single texture from file
    - @param: Texture file
    - @param: Alpha boolean
    - @return: Texture
    */
    static Texture loadTextureFromFile(const GLchar *file, GLboolean alpha);
};
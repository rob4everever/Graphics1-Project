/*
- Shader.hpp
-
- Author: 100086865
-
- Class that represents a generic shader. It generates,
- compiles and links a shader program from shader source
- files (GLSL). Provides functionality for easy management.
*/

#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <string>

class Shader {

public:

    //Shader ID
    GLuint ID;

    /*
    - Shader constructor
    */
    Shader() {};

    /*
    - Sets the current shader as active
    - @return: Active shader
    */
    Shader &use();

    /*
    - Compiles a shader from shader sources
    - @param: Vertex shader source
    - @param: Fragment shader source
    - @param: Geometry shader source (Optional)
    */
    void compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometryShader = nullptr);

    /*
    - Utility functions that set uniform variables in the shaders
    - @param: Shader name
    - @param: Value to insert
    - @param: Sets as active (FALSE)
    */
    void setFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
    void setInteger(const GLchar *name, GLint value, GLboolean useShader = false);
    void setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
    void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
    void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
    void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

private:

    /*
    - Checks for shader compilation and linking errors
    - @param: Shader object
    - @param: Error type
    */
    void checkCompileErrors(GLuint object, std::string type);
};
/*
- SpriteRenderer.hpp
-
- Author: 100086865
-
- Provides functionality to easily render a sprite
- to the screen.
*/

#pragma once

#include <Glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Texture.hpp"
#include "Shader.hpp"

class SpriteRenderer {

public:

    /*
    - Initialises render data and assigns the provided shader program
    */
    SpriteRenderer(Shader &shader);

    /*
    - SpriteRenderer destructor
    */
    ~SpriteRenderer();

    /*
    - Draws a sprite
    - @param: Texture of sprite
    - @param: Position of sprite
    - @param: Size of sprite
    - @param: Rotation of sprite
    - @param: Colour of sprite
    */
    void drawSprite(Texture &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 colour = glm::vec3(1.0f));

private:

    Shader shader;
    GLuint quadVAO;

    /*
    - Initializes and configures the quad's buffer and vertex attributes
    */
    void initRenderData();
};
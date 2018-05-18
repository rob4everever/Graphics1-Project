/*
- SpriteRenderer.hpp
-
- Author: 100086865
-
- Source file for Texture.hpp, contains function definitions.
*/

#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(Shader &shader) {
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::drawSprite(Texture &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 colour) {

    //Prepare transformations
    this->shader.use();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(position, 0.0f));

    //Typical transformation order should be scale, rotate, translate
    //Matrix multiplication done right to left so transformation code should be in reversed order
    //Move origin to the center of the quad to get expected rotations
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

                                                      //set shader uniform var
    this->shader.setMatrix4("model", model);

    //Render textured quad
    this->shader.setVector3f("spriteColor", colour);

    //Activate and bind texture
    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    //Bind VAO and draw
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData() {

    // Configure VAO and VBO
    GLuint VBO;
    GLfloat vertices[] = {
        //Position      //Texture
        0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 0.0f,
        0.0f, 0.0f,     0.0f, 0.0f,

        0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 1.0f,     1.0f, 1.0f,
        1.0f, 0.0f,     1.0f, 0.0f
    };

    //Generate buffers
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    //Bind data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
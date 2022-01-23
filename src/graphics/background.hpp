#pragma once
#include "shader.hpp"
#include <glad/glad.h>
namespace Graphics{

    class Background{
        public:
        Background(float width, float height):
        _width(width), 
        _height(height), 
        _shader(Graphics::Shaders::AbstractShader( "shaders/passthrough.vert", "shaders/spectrumbeam.frag"))
        {

            glGenVertexArrays(1, &vertexArrayObject);
            glGenBuffers(1, &vertexBufferObject);
            glBindVertexArray(vertexArrayObject);

            
            GLfloat vertices[] = {
                 // positions         // colors             //uvs
                -1.f, -1.f,  0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
                -1.f,  1.f,  0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                 1.f, -1.f,  0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
                -1.f,  1.f,  0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                 1.f, -1.f,  0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
                 1.f,  1.f,  0.0f,  1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
            };

            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            printf("Background initialized to %f %f\n", width, height);
        }
        void draw(){
            _shader.apply();
            _shader.setFloat("iTime", glfwGetTime());


            glBindVertexArray(vertexArrayObject);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            // color attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
            // uv attribute
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
            
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glDrawArrays(GL_TRIANGLES, 0, 6); // 3 index starting at 0
            
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
        }

        ~Background(){
            glDeleteVertexArrays(1, &vertexArrayObject);
            glDeleteBuffers(1, &vertexBufferObject);
        }
        private:
        Shaders::AbstractShader _shader;
        GLuint vertexBufferObject, vertexArrayObject;
        const float _width, _height;
    };

}
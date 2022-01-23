#pragma once
#include "shader.hpp"
#include <glad/glad.h>
namespace Graphics{

    class Background{
        public:
        Background(float width, float height, Shaders::AbstractShader &shader):_width(width), _height(height), _shader(shader){

            glGenBuffers(3, _buffers);

            
            static const GLfloat positions[] = {
                0,      0,       0.0f,
                0,      _height, 0.0f,
                _width, 0,       0.0f,
                0,      _height, 0.0f,
                _width, 0,       0.0f,
                _width, _height, 0.0f,
            };
            static const GLfloat colors[] = {
                -1.f, -1.f, 0.0f,
                -1.f,  1.f, 0.0f,
                 1.f, -1.f, 0.0f,
                -1.f,  1.f, 0.0f,
                 1.f, -1.f, 0.0f,
                 1.f,  1.f, 0.0f,
            };
            static const GLfloat uvs[] = {
                -1.f, -1.f,
                -1.f,  1.f,
                 1.f, -1.f,
                -1.f,  1.f,
                 1.f, -1.f,
                 1.f,  1.f,
            };
            
            glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, _buffers[1]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, _buffers[2]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
            printf("Background initialized to %f %f\n", width, height);
        }
        void draw(){
            _shader.apply();


            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, _buffers[1]);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, _buffers[2]);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

            glDrawArrays(GL_TRIANGLES, 0, 2); // 3 index starting at 0
            
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
            printf("Background drawn\n");
        }
        private:
        Shaders::AbstractShader &_shader;
        GLuint _buffers[3];
        const float _width, _height;
    };

}
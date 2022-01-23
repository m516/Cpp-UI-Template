#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



class Renderer;
namespace Graphics{
namespace Shaders{

    GLuint Load(const char * vertex_file_path,const char * fragment_file_path);

    class AbstractShader{
        public:
        virtual ~AbstractShader(){}
        /**
         * @brief Apply the shader. Run at the beginning of every draw call.
         * Only call in the Renderer class.
         */
        virtual void apply();
        /**
         * @brief Create the shader. Run once before the first draw call.
         * Only call in the Renderer class.
         */
        virtual void init();
        Renderer *_renderer;
        protected:
        GLuint _programID;
        std::string _vertexShaderFilename;
        std::string _fragmentShaderFilename;
        std::string _genShaderPath(const std::string &shaderFileName);
        /**
         * @brief Loads the shaders from the path
         * 
         */
        void _loadShaders();
    };

    class Passthrough : public AbstractShader{
        public:
        virtual void init(){
            _vertexShaderFilename = "shaders/passthrough.vert";
            _fragmentShaderFilename = "shaders/passthrough.frag";
            _loadShaders();
        }
    };
}
}


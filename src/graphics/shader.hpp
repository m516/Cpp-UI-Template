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


namespace Graphics{
namespace Shaders{

    GLuint Load(const char * vertex_file_path,const char * fragment_file_path);

    class AbstractShader{
        public:

        AbstractShader(const std::string &vertexShader, const std::string &fragmentShader) : _vertexShaderFilename(vertexShader), _fragmentShaderFilename(fragmentShader){
            _loadShaders();
        }


        virtual ~AbstractShader(){}
        /**
         * @brief Apply the shader. Run at the beginning of every draw call.
         * Only call in the Renderer class.
         */
        virtual void apply();

        // utility uniform functions
        // ------------------------------------------------------------------------
        void setBool(const std::string &name, bool value) const
        {         
            glUniform1i(glGetUniformLocation(_programID, name.c_str()), (int)value); 
        }
        // ------------------------------------------------------------------------
        void setInt(const std::string &name, int value) const
        { 
            glUniform1i(glGetUniformLocation(_programID, name.c_str()), value); 
        }
        // ------------------------------------------------------------------------
        void setFloat(const std::string &name, float value) const
        { 
            glUniform1f(glGetUniformLocation(_programID, name.c_str()), value); 
        }


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
}
}


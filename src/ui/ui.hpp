#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

namespace UI{
    
    // Fields
    namespace Window{
        extern GLFWwindow* window;
        extern int width, height;
        extern ImVec4 background_color;
    }


    void init();
    void update();
    void close();
}
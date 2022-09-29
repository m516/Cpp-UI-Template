# C++ UI Template
![CMake build](https://github.com/m516/Cpp-UI-Template/actions/workflows/cmake.yml/badge.svg)
![issues](https://img.shields.io/github/issues/m516/Cpp-UI-Template)
![forks](https://img.shields.io/github/forks/m516/Cpp-UI-Template)
![stars](https://img.shields.io/github/stars/m516/Cpp-UI-Template)
![license](https://img.shields.io/github/license/m516/Cpp-UI-Template)

This is a highly unstable framework for making snappy, interactive user interfaces with OpenGL 3+. I use it as a framework for building interactive, multithreaded computer vision applications with OpenCV, and you can too. 


### Setup (Ubuntu)
```sh
# Install dependencies
sudo apt-get update
sudo apt-get install -y build-essential git make cmake libopencv-dev xorg-dev
# Clone the repository (with libraries)
git clone https://github.com/m516/Cpp-UI-Template.git --recursive
# Building
cd Cpp-UI-Template
cmake .
make -j$(nproc)
```

The binary is in the src/ folder for some reason. I'll have to check that out 🤔

## Apps

Making an App is easy. Create a new folder in `src/apps` with the name of the app. Inside the folder make a new header. Name it something uselessly nebulous like "app.hpp"

Include important things:
```cpp
#pragma once
#include "ui/app.hpp"     // For the app template
#include <imgui/imgui.h>  // For making widgets
```

There a special namespace "apps" for all your apps. Make the class there so you don't mess up anyone else's code.
```cpp
namespace Apps{
class ImGui_Demo: public app::App{
    public:
```

Apps can inherit three methods: 
* `void uiInit()`, run once as soon as the app is initialized
* `void uiDraw()`, run repeatedly every frame.
* `void uiClose()`, run once when the app is closing.

Let's make a window with a button:
```cpp
    virtual void uiDraw(){
        ImGui::Begin("The Do-Nothing Button");
        ImGui::Button("Press me");
        ImGui::End();
    }
```
Note that ImGui documentation can be found in [its demo](https://github.com/m516/Cpp-UI-Template/blob/master/thirdparty/imgui/imgui_demo.cpp)

That's it! Now create the app in `main/main.cpp` and run the UI:
```cpp
int main()
{
    Apps::ImGui_Demo imgui_demo;
    imgui_demo.uiInit();

    UI::init();
    while(UI::Window::window) UI::update();
    return 0;
}
```
**Important:** Make sure all UI's are initialized BEFORE running UI::init(). I get that this process is extremely clunky, and I'll try to fix it soon.

Also, if you make any implementation (.cpp) files for your apps, make sure those are included in [src/CMakeLists.txt](https://github.com/m516/Cpp-UI-Template/blob/with-opencv/src/CMakeLists.txt). (I know, this is also super inconvenient. I won't make any promises, but there might be an update that makes this step unnecessary.)

## The whole example
```cpp
#pragma once
#include "ui/app.hpp"
#include <imgui/imgui.h>


namespace Apps{

class ImGui_Demo: public app::App{
    public:

    virtual void uiDraw(){
        ImGui::ShowDemoWindow(NULL);
    }

}; // End class ImGui_Demo

} // End namespace Apps
```

**More extensive documentation is underway, but the [existing apps](https://github.com/m516/Cpp-UI-Template/tree/with-opencv/src/apps) can be used for reference.** 

### Libraries and Licenses
My work is under the [MIT License](https://github.com/m516/Cpp-UI-Template/blob/with-opencv/LICENSE) with libraries whose licenses are as follows:


|                           Name |                                                         Installation instructions                                                         | License                                                                            | Github Repository                            |
| -----------------------------: | :---------------------------------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------- | :------------------------------------------- |
|  [OpenCV](https://opencv.org/) |   [official instructions as of 7/13/2020 (volatile)](https://docs.opencv.org/master/df/d65/tutorial_table_of_content_introduction.html)   | [3-clause BSD License](https://opencv.org/license/)                                | [yes](https://github.com/opencv/opencv)      |
| [GLAD](https://glad.dav1d.de/) | Included in project [(Unofficial instructions)](https://learnopengl.com/Getting-started/Creating-a-window) (path to KHR library modified) | [Varies](https://github.com/Dav1dde/glad#whats-the-license-of-glad-generated-code) | [Generator](https://github.com/Dav1dde/glad) |
|  [GLFW](https://www.glfw.org/) |                        Included in project [(Official instructions)](https://github.com/glfw/glfw#compiling-glfw)                         | [zlib license](extern/glfw/LICENSE)                                                | [yes](https://github.com/glfw/glfw)          |
|                          ImGui |                                                   Included in project (static library)                                                    | [MIT License](extern/imgui/LICENSE)                                                | [yes](https://github.com/ocornut/imgui)      |



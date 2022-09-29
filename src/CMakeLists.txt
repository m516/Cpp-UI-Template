# CMakeList.txt : CMake project for CV-Sandbox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# This is the name of the executable
set(EXECUTABLE_NAME JACT)

# In UNIX, set PROJECT_SOURCES using the following command
# find . | grep .cpp
# Delete the ./ at the beginning of each file with block selection (alt + shift in Visual Studio)
set(PROJECT_SOURCES
"ui/app.cpp"
"ui/ui_utils.cpp"
"ui/ui_implementation.cpp"
"apps/Webcam/app.cpp"
"apps/Thresholding/app.cpp"
"graphics/mat_viewer.cpp"
"graphics/background.cpp"
"graphics/shader.cpp"
"main/main.cpp"
)

# In UNIX, set PROJECT_HEADERS using the following command
# find . | grep .hpp
# Delete the ./ at the beginning of each file with block selection (alt + shift in Visual Studio)

# Add source to this project's executable.
add_executable (${EXECUTABLE_NAME} ${PROJECT_SOURCES})

# Add tests and install targets if needed.
target_link_libraries (${EXECUTABLE_NAME} glad glm glfw imgui ${OpenCV_LIBS}) 
target_include_directories(${EXECUTABLE_NAME} PUBLIC src)

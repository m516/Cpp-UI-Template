# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

# Define colors
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColorReset "${Esc}[m")
  set(ColorBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

project ("JACT" C CXX)

# Set the macro/helper directory 
set(MACRO_DIRECTORY ${CMAKE_HOME_DIRECTORY}/CMake/macros)
message("${BoldMagenta}CMake utility directory: ${MACRO_DIRECTORY}${ColorReset}")
# Add some macros
include(${MACRO_DIRECTORY}/libhelpers.cmake)

# Find packages used throughout this repository

message("${BoldYellow}Searching for libraries...${ColorReset}")


# Threads
message("${BoldYellow}Finding Threads${ColorReset}")
option(USE_THREADS "Attempt to use pthread library. If disabled, some projects will use a single thread or refuse to build. Enabled by default" ON)
if(USE_THREADS)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    include(FindThreads)
    if(CMAKE_USE_PTHREADS_INIT)
        message("${BoldYellow}Threads library found.${ColorReset}")
        #Add compiler definition to tell code it can use threads. The value of the definition is the number of cores.
        if(CMAKE_VERSION VERSION_GREATER 3.12)
            include(ProcessorCount)
            ProcessorCount(N_PROCESSORS)
            if(N_PROCESSORS EQUAL 0)
                set(N_PROCESSORS 2)
                message("${BoldYellow}Unable to count processors${ColorReset}")
            endif()
            message("${BoldYellow}Max supported thread count estimated to be ${N_PROCESSORS}${ColorReset}")
            add_compile_definitions(THREAD_SUPPORT=${N_PROCESSORS})
        else()
            add_definitions("-DTHREAD_SUPPORT=\"${N_PROCESSORS}\"")
        endif()
    else()
        if(Threads_FOUND)
            message("${BoldRed}A threading library was found, but it isn't pthread.${ColorReset}")
        else()
            message("${BoldRed}Threads library wasn't found.${ColorReset}")
        endif()
    endif()
else()
    message("${BoldRed}Threads library was disabled.${ColorReset}")
endif()

# OpenCV
message("${BoldYellow}Finding OpenCV${ColorReset}")
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

# glad
message("${BoldYellow}Using local copy of GLAD${ColorReset}")
add_subdirectory(thirdparty/glad)
include_directories(thirdparty)

# glfw
message("${BoldYellow}Using local copy of GLFW${ColorReset}")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)

# Dear ImGui
message("${BoldYellow}Using local copy of ImGui${ColorReset}")
add_subdirectory(thirdparty/imgui)

# glm
message("${BoldYellow}Using local copy of GLM${ColorReset}")
add_subdirectory(thirdparty/glm)
include_directories(thirdparty/glm)

# Google Test
# message("${BoldYellow}Fetching the latest Google Test framework${ColorReset}")
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)
message("${BoldYellow}Using local copy of the Google Test framework${ColorReset}")
add_subdirectory(thirdparty/googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# units -- disabled until needed
# message("${BoldYellow}Searching for an installed version of mp-units${ColorReset}")
# message("This dependency will likely be a standard C++ library, so this is just a temporary workaround until then")
# message("It also doesn't like to be loaded locally.")
# message("If you do find a way to load this project locally, please send an issue or PR my way!")
# find_package(mp-units CONFIG REQUIRED)

message("${BoldYellow}Library search complete!${ColorReset}")

message("${BoldYellow}Checking OpenMP support${ColorReset}")
include(FindOpenMP)
if(OpenMP_FOUND)
    if(OpenMP_C_FOUND)
        message("-- C version: ${OpenMP_C_VERSION}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    endif()
    if(OpenMP_CXX_FOUND)
        message("-- C++ version: ${OpenMP_CXX_VERSION}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    endif()
endif()


# Uncomment when the project uses CUDA
# #CUDA
# message("${BoldYellow}Checking if CUDA files can be compiled${ColorReset}")
# option(USE_CUDA "Attempt to use CUDA. If disaled, projects that require CUDA can't build. Enabled by default" ON)
# #https://cliutils.gitlab.io/modern-cmake/chapters/packages/CUDA.html
# if(USE_CUDA)
#     include(CheckLanguage)
#     check_language(CUDA)
#     if(CMAKE_CUDA_COMPILER)
#         message("${BoldYellow}CUDA exists${ColorReset}")
#         enable_language(CUDA)
#         include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
#         if(NOT DEFINED CMAKE_CUDA_STANDARD)
#             set(CMAKE_CUDA_STANDARD 11)
#             set(CMAKE_CUDA_STANDARD_REQUIRED ON)
#         endif()
#     else()
#         message("${BoldRed}Failed to find CUDA. Some projects can't be run.${ColorReset}")
#     endif()
# else()
#     message("${BoldRed}CUDA was disabled.${ColorReset}")
# endif()
    

# Include sub-projects.
include_directories("src")
add_subdirectory ("src")


# Include tests.
include(CTest)
add_subdirectory ("test")
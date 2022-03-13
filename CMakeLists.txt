cmake_minimum_required(VERSION 3.21)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

# OpenGL
find_package(OpenGL REQUIRED)

set(LIBS_PATH "src/libs" CACHE PATH "libraries directory" )
link_directories(${LIBS_PATH})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(GLFW_INCLUDE_PATH "src/include" CACHE PATH "The directory that contains GL/glfw.h" )
set(GLFW_LIBRARY "glfw3.lib" CACHE FILEPATH "libglfw.a or glfw.lib" )

#set(GLEW_INCLUDE_PATH "" CACHE PATH "The directory that contains GL/glew.h" )
#set(GLEW_LIBRARY "" CACHE FILEPATH "libglew.a or glew.lib" )

#set(GLM_INCLUDE_PATH "" CACHE PATH "The directory that contains glm/glm.hpp" )

set(MY_HEADER_FILES
        # put all your .h here. Right now we have none.
        # Example :
        # ../common/shader.hpp
        )

set(MY_SOURCE_FILES
        # put all your .c/.cpp here.
        src/main.cpp
        src/glad.c
        # ../common/shader.cpp
        )



include_directories(
        ${GLFW_INCLUDE_PATH}

        #${GLEW_INCLUDE_PATH}
        #${GLM_INCLUDE_PATH}
)

add_executable(LearnOpenGL
        ${MY_HEADER_FILES}
        ${MY_SOURCE_FILES}
        )
target_link_libraries(LearnOpenGL
        ${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
        ${GLFW_LIBRARY}
        #${GLEW_LIBRARY}
        )
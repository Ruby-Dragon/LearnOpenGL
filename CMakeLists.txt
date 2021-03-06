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
        src/include/read_file.hpp
        src/include/shader.hpp src/include/image/stb_image.h)

set(MY_SOURCE_FILES
        # put all your .c/.cpp here.
        src/main.cpp
        src/glad.c
        # ../common/shader.cpp
        src/read_file.cpp src/shader.cpp src/stb_image_impl..cpp)

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

add_custom_command(
        TARGET LearnOpenGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/shaders $<TARGET_FILE_DIR:LearnOpenGL>/shaders
        COMMENT "Copying shaders" VERBATIM
)

add_custom_command(
        TARGET LearnOpenGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:LearnOpenGL>/textures
        COMMENT "Copying shaders" VERBATIM
)
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "read_file.hpp"
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//SHADERS

	std::string shaderSourceBuffer;

	//vertex.vsh
	shaderSourceBuffer =  readFile("shaders/vertex.vsh");
	const char* vertexShaderSource = shaderSourceBuffer.c_str();
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	//end vertex.vsh

	//fragment.fsh
	shaderSourceBuffer =  readFile("shaders/fragment.fsh");
	const char* fragmentShaderSource = shaderSourceBuffer.c_str();
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	//end fragment.fsh

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//END SHADERS

	//triangle
    float vertices[] = {
            // positions                // colors
            0.5f, -0.5f,      0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
            -0.5f, -0.5f,     0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
            0.0f,  0.5f,    0.0f,  0.0f, 0.0f, 1.0f    // top
    };

	//make VBO
	unsigned int VBO;
    //VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    //VBO
	glGenBuffers(1, &VBO);
    //Bind VAO
	glBindVertexArray(VAO);

	//Bind buffers to VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//set vertex attributes pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(shaderProgram);


	//render loop
	while(!glfwWindowShouldClose(window))
	{
		//process window input
		processInput(window);

        //clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //shaders run
		glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

		//render to screen
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
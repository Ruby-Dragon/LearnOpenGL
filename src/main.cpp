#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.hpp"

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

	Shader ourShader = Shader("shaders/vertex.vsh", "shaders/fragment.fsh");
    ourShader.use();

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

    glUseProgram(ourShader.ID);


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
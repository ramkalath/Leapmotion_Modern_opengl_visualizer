/*****************************************************************************
 * Filename : main.cpp from 10_camera_transfrom_333
 * Date : 16/Dec/2017
 * Author : Ram
 * Email : ramkalath@gmail.com
 * Breif Description : spin a camera around an object and make sure the camera only points to the object
 * Detailed Description :
 * Last Modified : 16/Dec/2017
 *****************************************************************************/

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include "Shader.h"
#include "SOIL.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../include/Leap.h"

using namespace std;

int width_screen = 640, height_screen = 480;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	// When the user presses the escape key, we set the window should close property to true, and close the application.
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	// glfw stuff ====================================================================
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(width_screen, height_screen, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    if(window == nullptr)
    {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
    }
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// Viewport dimensions
	glfwGetFramebufferSize(window, &width_screen, &height_screen);
	glViewport(0, 0, width_screen, height_screen);

	Shader ourShader("vertex_shader.vert", "fragment_shader.frag");
	// ================================================================================

	// data - vertices ===================================================================
	GLfloat scalex = (GLfloat)width_screen/(GLfloat)width_screen;
	GLfloat scaley = (GLfloat)height_screen/(GLfloat)width_screen;
	GLfloat vertices[] =
	{
		-1.5f*scalex, -1.5f*scaley, 0.0f, 0.0f, 0.0f,
		 1.5f*scalex, -1.5f*scaley, 0.0f, 1.0f, 0.0f,
		-1.5f*scalex,  1.5f*scaley, 0.0f, 0.0f, 1.0f,
		 1.5f*scalex,  1.5f*scaley, 0.0f, 1.0f, 1.0f,
		 1.5f*scalex, -1.5f*scaley, 0.0f, 1.0f, 0.0f,
		-1.5f*scalex,  1.5f*scaley, 0.0f, 0.0f, 1.0f
	};

	// ==================================================================================
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Postion Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO

	// =================================================================================
	// Texture Stuff
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float theta = glm::radians(-90.0f);

	// Leap Motion stuff ======================================================
	Leap::Controller controller;
	
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

		ourShader.Use();
		GLfloat model_matrix_data[16] = {1, 0,           0,          0,
										 0, cos(theta),  sin(theta), 0, 
										 0, -sin(theta), cos(theta), 0, 
										 0, -1.0,       -3.1,         1}; 

		GLfloat view_matrix_data[16] = {1, 0, 0, 0, 
										0, 1, 0, 0, 
										0, 0, 1, 0, 
										0, 0, 0, 1}; 

		glm::mat4 model_matrix = glm::make_mat4(model_matrix_data);
		glm::mat4 view_matrix = glm::make_mat4(view_matrix_data);
		glm::mat4 projection_matrix = glm::perspective(45.0f, (GLfloat)width_screen/(GLfloat)height_screen, 0.1f, 10.0f);

		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection_matrix));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		//HandList hands = frame.hands();
		//for(HandList::const_iterator hl = hands.begin(); hl!=hands.end(); hl++)
		//{
			//// Draw Palm
			//const Hand hand = *hl;
			//float palmX = hand.palmPosition().x;
			//float palmY = hand.palmPosition().y;
			//float palmZ = hand.palmPosition().z;
		//}
		//std::cout << palmX << "," << palmY << "," << plamZ << std::endl;
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
    return 0;
}

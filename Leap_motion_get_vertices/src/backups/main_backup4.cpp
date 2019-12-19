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
#include <math.h>

using namespace std;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	// When the user presses the escape key, we set the window should close property to true, and close the application.
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int width_screen = 640, height_screen = 480;

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

	Shader shader_bottom_plate("vertex_shader_bottom_plate.vert", "fragment_shader_bottom_plate.frag");
	// ================================================================================

	// data - vertices ===================================================================
	GLfloat scalex = (GLfloat)width_screen/(GLfloat)width_screen;
	GLfloat scaley = (GLfloat)height_screen/(GLfloat)width_screen;

	GLfloat bottom_plate_vertices[] =
	{
		-1.5f*scalex, -1.5f*scaley, 0.0f, 0.0f, 0.0f,
		 1.5f*scalex, -1.5f*scaley, 0.0f, 1.0f, 0.0f,
		-1.5f*scalex,  1.5f*scaley, 0.0f, 0.0f, 1.0f,
		 1.5f*scalex,  1.5f*scaley, 0.0f, 1.0f, 1.0f,
		 1.5f*scalex, -1.5f*scaley, 0.0f, 1.0f, 0.0f,
		-1.5f*scalex,  1.5f*scaley, 0.0f, 0.0f, 1.0f
	};

	GLfloat cube_vertices[] = {
		-0.05f, -0.05f, -0.05f,  0.0f, 0.0f,
		 0.05f, -0.05f, -0.05f,  1.0f, 0.0f,
		 0.05f,  0.05f, -0.05f,  1.0f, 1.0f,
		 0.05f,  0.05f, -0.05f,  1.0f, 1.0f,
		-0.05f,  0.05f, -0.05f,  0.0f, 1.0f,
		-0.05f, -0.05f, -0.05f,  0.0f, 0.0f,

		-0.05f, -0.05f,  0.05f,  0.0f, 0.0f,
		 0.05f, -0.05f,  0.05f,  1.0f, 0.0f,
		 0.05f,  0.05f,  0.05f,  1.0f, 1.0f,
		 0.05f,  0.05f,  0.05f,  1.0f, 1.0f,
		-0.05f,  0.05f,  0.05f,  0.0f, 1.0f,
		-0.05f, -0.05f,  0.05f,  0.0f, 0.0f,

		-0.05f,  0.05f,  0.05f,  1.0f, 0.0f,
		-0.05f,  0.05f, -0.05f,  1.0f, 1.0f,
		-0.05f, -0.05f, -0.05f,  0.0f, 1.0f,
		-0.05f, -0.05f, -0.05f,  0.0f, 1.0f,
		-0.05f, -0.05f,  0.05f,  0.0f, 0.0f,
		-0.05f,  0.05f,  0.05f,  1.0f, 0.0f,

		 0.05f,  0.05f,  0.05f,  1.0f, 0.0f,
		 0.05f,  0.05f, -0.05f,  1.0f, 1.0f,
		 0.05f, -0.05f, -0.05f,  0.0f, 1.0f,
		 0.05f, -0.05f, -0.05f,  0.0f, 1.0f,
		 0.05f, -0.05f,  0.05f,  0.0f, 0.0f,
		 0.05f,  0.05f,  0.05f,  1.0f, 0.0f,

		-0.05f, -0.05f, -0.05f,  0.0f, 1.0f,
		 0.05f, -0.05f, -0.05f,  1.0f, 1.0f,
		 0.05f, -0.05f,  0.05f,  1.0f, 0.0f,
		 0.05f, -0.05f,  0.05f,  1.0f, 0.0f,
		-0.05f, -0.05f,  0.05f,  0.0f, 0.0f,
		-0.05f, -0.05f, -0.05f,  0.0f, 1.0f,

		-0.05f,  0.05f, -0.05f,  0.0f, 1.0f,
		 0.05f,  0.05f, -0.05f,  1.0f, 1.0f,
		 0.05f,  0.05f,  0.05f,  1.0f, 0.0f,
		 0.05f,  0.05f,  0.05f,  1.0f, 0.0f,
		-0.05f,  0.05f,  0.05f,  0.0f, 0.0f,
		-0.05f,  0.05f, -0.05f,  0.0f, 1.0f
    };
	// ==================================================================================
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bottom_plate_vertices), bottom_plate_vertices, GL_STATIC_DRAW);

	// Postion Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO

	// =================================================================================
	// Texture Stuff
	GLuint bottom_plate_texture;
	glGenTextures(1, &bottom_plate_texture);
	glBindTexture(GL_TEXTURE_2D, bottom_plate_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image_bottom_plate = SOIL_load_image("./container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_bottom_plate);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image_bottom_plate);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// setup vaos, vbos and define attributes for cube ======================
	GLuint VBO_cube, VAO_cube;
	glGenVertexArrays(1, &VAO_cube);
	glGenBuffers(1, &VBO_cube);

	glBindVertexArray(VAO_cube);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	// Postion Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO

	//setup textures for cube ================================================
	// Texture Stuff
	GLuint cube_texture;
	glGenTextures(1, &cube_texture);
	glBindTexture(GL_TEXTURE_2D, cube_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width_cube_texture, height_cube_texture;
	unsigned char* image_cube = SOIL_load_image("./cube_texture.jpg", &width_cube_texture, &height_cube_texture, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_cube_texture, height_cube_texture, 0, GL_RGB, GL_UNSIGNED_BYTE, image_cube);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image_cube);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// ========================================================================
	float theta = glm::radians(-90.0f);
	//float theta_cube = glm::radians(-45.0f);

	// Leap Motion stuff ======================================================
	Leap::Controller controller;
	
	glm::vec3 cubePositions[] = {
							glm::vec3(0.0f, 0.0f, -6.1f),
							glm::vec3(0.7f, 0.2f, -0.3f),
							glm::vec3(0.6f,-0.7f, -0.5f)
	};

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// lets draw the first object ---------------------------------------------------------------------------------------
		shader_bottom_plate.Use();

		GLfloat model_matrix_data_bottom_template[16] = {1, 0, 0, 0,
										 0, cos(theta),  sin(theta), 0, 
										 0, -sin(theta), cos(theta), 0, 
										 0, -1.0, -3.1, 1}; 

		GLfloat view_matrix_data_bottom_template[16] = {1, 0, 0, 0, 
														0, 1, 0, 0, 
														0, 0, 1, 0, 
														0, 0, 0, 1}; 

		glm::mat4 model_matrix = glm::make_mat4(model_matrix_data_bottom_template);
		glm::mat4 view_matrix = glm::make_mat4(view_matrix_data_bottom_template);
		glm::mat4 projection_matrix = glm::perspective(45.0f, (GLfloat)width_screen/(GLfloat)height_screen, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader_bottom_plate.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(glGetUniformLocation(shader_bottom_plate.Program, "view"), 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(glGetUniformLocation(shader_bottom_plate.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection_matrix));

		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, bottom_plate_texture);
		glUniform1i(glGetUniformLocation(shader_bottom_plate.Program, "ourTexture1"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// now for the second object - cube----------------------------------------------------------------------------------

		GLfloat view_matrix_data_cube[16] = {1, 0, 0, 0, 
											 0, 1, 0, 0, 
											 0, 0, 1, 0, 
											 0, 0, 0, 1}; 

		glm::mat4 view_matrix_cube = glm::make_mat4(view_matrix_data_cube);
		glm::mat4 projection_matrix_cube = glm::perspective(45.0f, (GLfloat)width_screen/(GLfloat)height_screen, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader_bottom_plate.Program, "view"), 1, GL_FALSE, glm::value_ptr(view_matrix_cube));
		glUniformMatrix4fv(glGetUniformLocation(shader_bottom_plate.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection_matrix_cube));

		glBindVertexArray(VAO_cube);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cube_texture);
		glUniform1i(glGetUniformLocation(shader_bottom_plate.Program, "ourTexture1"), 0);

		for(int i=0; i<3; i++)
		{
			GLfloat cube_rotation_model[16] = {1, 0, 0, 0, 
											 0, 1, 0, 0, 
											 0, 0, 1, 0, 
											 0, 0, -3, 1}; 
			glm::mat4 model_matrix_cube = glm::make_mat4(cube_rotation_model);
			model_matrix_cube = glm::translate(model_matrix_cube, cubePositions[i]);
			glUniformMatrix4fv(glGetUniformLocation(shader_bottom_plate.Program, "model"), 1, GL_FALSE, glm::value_ptr(model_matrix_cube));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
    return 0;
}

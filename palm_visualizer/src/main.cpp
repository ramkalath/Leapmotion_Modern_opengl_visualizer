/*****************************************************************************
 * Author : Ram
 * Date : 19/Dec/2019
 * Email : ramkalath@gmail.com
 * Breif Description : handvisualizer with leapmotion
 * Detailed Description : working fine as a VR visualizer
 *						 TODO(ram): yet to make it AR; lots of work left for that				
 * 						 TODO(ram): draw line primitives between the finger joints (not too critical)
 *                       DONE(ram): https://developer.leapmotion.com/documentation/v4/vrar.html follow that post to convert it from table top to head mount
 *						 TODO(ram): test the above point
 *****************************************************************************/
// GLEW and GLFW includes
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// glm includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other popular includes
#include <iostream>
#include <chrono>

// User created headers
#include "../include/shader.h"
#include "../include/modelloader.h"
#include "../include/gamesettings.h"

// Leap motion includes
#include "../include/finger_joints.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
	// When the user presses the escape key, we set the window should close property to true, and close the application.
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int width = 640, height = 800;
int spread = 150;

int main()
{
	Hands hand;
	GameSettings globalsettings;
	// glfw stuff ====================================================================
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Lighting Properties", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    if(window == nullptr) {
    	std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
    }
	glewExperimental = GL_TRUE; 
	if(glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader objectshader("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");

	modelloader icosphere("./resources/icosphere/icosphere.obj");

	//TODO(ram): I think this is right. But have to experiment more
	glm::mat4 rotation_matrix = glm::mat4{1, 0,  0, 0,
										   0, 1, 0, 0,
										   0, 0,  1, 0,
										   0, 0, 0, 1};
	//glm::mat4 rotation_matrix = glm::mat4{-1, 0,  0, 1,
										   //0, 0, -1, 1,
										   //0,-1,  0, 1,
										   //0, 0, 0, 1};
	//rotation_matrix = glm::transpose(rotation_matrix);


	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// draw object ---------------------------------------------------------------
        glUseProgram(objectshader.program);

		// Uniforms
		glUniformMatrix4fv(glGetUniformLocation(objectshader.program, "view"), 1, GL_FALSE, glm::value_ptr(globalsettings.view));
		glUniformMatrix4fv(glGetUniformLocation(objectshader.program, "projection"), 1, GL_FALSE, glm::value_ptr(globalsettings.projection_perspective));
		glUniform3f(glGetUniformLocation(objectshader.program, "LightDirection"), 0.0f, 0.0f, -10.0f);
		glUniform3f(glGetUniformLocation(objectshader.program, "LightAmbient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(objectshader.program, "LightDiffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(objectshader.program, "LightSpecular"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(objectshader.program, "CameraPosition"), 0.0f, 0.0f, 0.0f);
		

		if(hand.detect_hands())
		{
			for(unsigned long i=0; i<hand.vertices_hand.size(); i++)
			{
				// Print joint positions
				//std::cout << "joint " << i << "\t"
						  //<< hand.vertices_hand[i].x/200 << "\t"
						  //<< hand.vertices_hand[i].y/200 << "\t"
						  //<< hand.vertices_hand[i].z/200 << std::endl;

				icosphere.modelmatrix = {0.07, 0.0f, 0.0f, 0.0f,
										 0.0f, 0.07, 0.0f, 0.0f, 
										 0.0f, 0.0f, 0.07f, 0.0f, 
										 hand.vertices_hand[i].x/spread, hand.vertices_hand[i].y/spread, hand.vertices_hand[i].z/spread, 1.0f};
				icosphere.modelmatrix = rotation_matrix * icosphere.modelmatrix;
						  
				glUniformMatrix4fv(glGetUniformLocation(objectshader.program, "model"), 1, GL_FALSE, glm::value_ptr(icosphere.modelmatrix));
				icosphere.RenderModel();
			}
		}

		glfwSwapBuffers(window);
	}
	glfwTerminate();
    return 0;
}

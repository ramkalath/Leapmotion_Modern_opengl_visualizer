/*****************************************************************************
 * Author : Ram
 * Date : 19/Dec/2019
 * Email : ramkalath@gmail.com
 * Breif Description : icosphere rendering
 * Detailed Description : icosphere loading with assimp
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

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	// When the user presses the escape key, we set the window should close property to true, and close the application.
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int width = 640, height = 800;

int main()
{
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
	icosphere.modelmatrix = {1.0f, 0.0f, 0.0f, 0.0f,
							 0.0f, 1.0f, 0.0f, 0.0f, 
							 0.0f, 0.0f, 1.0f, 0.0f, 
							 0.0f, 0.0f, 0.0f, 1.0f};
	//icosphere.modelmatrix = glm::translate(icosphere.modelmatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	//icosphere.modelmatrix = glm::rotate(icosphere.modelmatrix, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	icosphere.modelmatrix = glm::scale(icosphere.modelmatrix, glm::vec3(0.1f, 0.1f, 0.1f));


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
		
		// render icosphere
		glUniformMatrix4fv(glGetUniformLocation(objectshader.program, "model"), 1, GL_FALSE, glm::value_ptr(icosphere.modelmatrix));

		auto start = std::chrono::high_resolution_clock::now();
		icosphere.RenderModel();
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
		std::cout << "time taken for rendering = " << duration.count() << " microseconds" << std::endl;

		glfwSwapBuffers(window);
	}
	glfwTerminate();
    return 0;
}

//includes
#pragma once
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

void draw_square_cuboid(glm::vec3 start, glm::vec3 end, GLfloat thickness)
{
	GLfloat height = sqrt(pow(end.x-start.x, 2) + pow(end.y-start.y, 2) + pow(end.z-start.z, 2));
	GLfloat scale_x = thickness, scale_z = thickness;
	float vertices[] = {
		-1.0f*scale_x, -1.0f*height, -1.0f*scale_z, 0.0f, 0.0f,
		 1.0f*scale_x, -1.0f*height, -1.0f*scale_z, 1.0f, 0.0f,
		 1.0f*scale_x,  1.0f*height, -1.0f*scale_z, 1.0f, 1.0f,
		 1.0f*scale_x,  1.0f*height, -1.0f*scale_z, 1.0f, 1.0f,
		-1.0f*scale_x,  1.0f*height, -1.0f*scale_z, 0.0f, 1.0f,
		-1.0f*scale_x, -1.0f*height, -1.0f*scale_z, 0.0f, 0.0f,
                           
		-1.0f*scale_x, -1.0f*height,  1.0f*scale_z, 0.0f, 0.0f,
		 1.0f*scale_x, -1.0f*height,  1.0f*scale_z, 1.0f, 0.0f,
		 1.0f*scale_x,  1.0f*height,  1.0f*scale_z, 1.0f, 1.0f,
		 1.0f*scale_x,  1.0f*height,  1.0f*scale_z, 1.0f, 1.0f,
		-1.0f*scale_x,  1.0f*height,  1.0f*scale_z, 0.0f, 1.0f,
		-1.0f*scale_x, -1.0f*height,  1.0f*scale_z, 0.0f, 0.0f,
                           
		-1.0f*scale_x,  1.0f*height,  1.0f*scale_z, 1.0f, 0.0f,
		-1.0f*scale_x,  1.0f*height, -1.0f*scale_z, 1.0f, 1.0f,
		-1.0f*scale_x, -1.0f*height, -1.0f*scale_z, 0.0f, 1.0f,
		-1.0f*scale_x, -1.0f*height, -1.0f*scale_z, 0.0f, 1.0f,
		-1.0f*scale_x, -1.0f*height,  1.0f*scale_z, 0.0f, 0.0f,
		-1.0f*scale_x,  1.0f*height,  1.0f*scale_z, 1.0f, 0.0f,
                           
		 1.0f*scale_x,  1.0f*height,  1.0f*scale_z, 1.0f, 0.0f,
		 1.0f*scale_x,  1.0f*height, -1.0f*scale_z, 1.0f, 1.0f,
		 1.0f*scale_x, -1.0f*height, -1.0f*scale_z, 0.0f, 1.0f,
		 1.0f*scale_x, -1.0f*height, -1.0f*scale_z, 0.0f, 1.0f,
		 1.0f*scale_x, -1.0f*height,  1.0f*scale_z, 0.0f, 0.0f,
		 1.0f*scale_x,  1.0f*height,  1.0f*scale_z, 1.0f, 0.0f,
                           
		-1.0f*scale_x, -1.0f*height, -1.0f*scale_z, 0.0f, 1.0f,
		 1.0f*scale_x, -1.0f*height, -1.0f*scale_z, 1.0f, 1.0f,
		 1.0f*scale_x, -1.0f*height,  1.0f*scale_z, 1.0f, 0.0f,
		 1.0f*scale_x, -1.0f*height,  1.0f*scale_z, 1.0f, 0.0f,
		-1.0f*scale_x, -1.0f*height,  1.0f*scale_z, 0.0f, 0.0f,
		-1.0f*scale_x, -1.0f*height, -1.0f*scale_z, 0.0f, 1.0f,
                           
		-1.0f*scale_x,  1.0f*height, -1.0f*scale_z, 0.0f, 1.0f,
		 1.0f*scale_x,  1.0f*height, -1.0f*scale_z, 1.0f, 1.0f,
		 1.0f*scale_x,  1.0f*height,  1.0f*scale_z, 1.0f, 0.0f,
		 1.0f*scale_x,  1.0f*height,  1.0f*scale_z, 1.0f, 0.0f,
		-1.0f*scale_x,  1.0f*height,  1.0f*scale_z, 0.0f, 0.0f,
		-1.0f*scale_x,  1.0f*height, -1.0f*scale_z, 0.0f, 1.0f
    };
}


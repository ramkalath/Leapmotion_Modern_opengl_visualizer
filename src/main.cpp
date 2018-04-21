/*****************************************************************************
 * Filename : main.cpp from 10_camera_transfrom_3
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
#include "./finger_joints.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace std;

int main()
{
	Hands hand;
	while(1){
		if(hand.detect_hands())
			std::cout << "hands detected" << std::endl;
		std::cout << hand.vertices_hand[0].x << std::endl;
		std::cout << hand.vertices_hand[0].y << std::endl;
		std::cout << hand.vertices_hand[0].z << std::endl;
		std::cout << hand.vertices_hand.size() << std::endl;
		std::cout << "-------------------------------------" << std::endl;
	}
    return 0;
}

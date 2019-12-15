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

using namespace std;

int main()
{
	// Leap Motion stuff ======================================================
	Leap::Controller controller;
	while(1)
	{
		Leap::Frame frame = controller.frame();
		Leap::HandList handlist = frame.hands();
		const Leap::Hand hand0 = handlist[0];
		const Leap::Hand hand1 = handlist[1];

		// wrist, palm,fingers 
		if(hand0.isValid())
		{
			if(hand0.isLeft())
			{
				std::cout << "Hand0 : Hand is left" << std::endl;
				
				Leap::FingerList fingers = frame.hands()[0].fingers();
				for(Leap::FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); fl++)
				{
					Leap::Bone bone;
					Leap::Bone::Type boneType;
					for(int b = 0; b < 4; b++)
					{
						boneType = static_cast<Leap::Bone::Type>(b);
						bone = (*fl).bone(boneType);
						std::cout << "Finger index: " << (*fl).type() << " " << bone << std::endl;
						std::cout << bone.prevJoint().x << std::endl;
						std::cout << bone.prevJoint().y << std::endl;
						std::cout << bone.prevJoint().z << std::endl;
					}
				}
			}
			else
			{
				std::cout << "Hand0 : Hand is right" << std::endl;
				//RightHandPositions();
			}
		}

		if(hand1.isValid())
		{
			if(hand1.isLeft())
			{
				std::cout << "Hand1 : Hand is left" << std::endl;
				//LeftHandPositions();
			}
			else
			{
				std::cout << "Hand0 : Hand is right" << std::endl;
				//RightHandPositions();
			}
		}
	}
    return 0;
}

#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/Leap.h"

class Hands{
public:
	Leap::Controller controller;
	std::vector<glm::vec3> vertices_hand;
	bool detect_hands();
	void populate_hand_vertex_list(Leap::Hand);

private:
	Leap::Frame frame; 
	Leap::HandList handlist;
};


bool Hands::detect_hands() {
	vertices_hand.erase(vertices_hand.begin(), vertices_hand.end());
	this->frame = controller.frame();
	bool x = 0;
	this->handlist = frame.hands();
	if(handlist[0].isValid()) {
		populate_hand_vertex_list(this->handlist[0]);
		//if(handlist[0].isLeft())
			//std::cout << "Left Hand" << std::endl;
		//if(handlist[0].isRight())
			//std::cout << "Right Hand" << std::endl;
		x = 1;
	}
	if(this->handlist[1].isValid()){
		populate_hand_vertex_list(this->handlist[1]);
		//if(handlist[0].isLeft())
			//std::cout << "Left Hand" << std::endl;
		//if(handlist[0].isRight())
			//std::cout << "Right Hand" << std::endl;
		x = 1;
	}
	if(x == 0){
		vertices_hand.push_back(glm::vec3(0,0,0));
	}
	return x;
}

void Hands::populate_hand_vertex_list(Leap::Hand hand){
	Leap::FingerList fingers = hand.fingers();
	for(Leap::FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); fl++){
		glm::vec3 finger_joint;
		Leap::Bone bone;
		Leap::Bone::Type boneType;
		for(int b = 0; b < 4; b++)
		{
			boneType = static_cast<Leap::Bone::Type>(b);
			bone = (*fl).bone(boneType);
			//std::cout << "Finger index: " << (*fl).type() << " " << bone << std::endl;
			finger_joint = glm::vec3(bone.prevJoint().x, bone.prevJoint().y, bone.prevJoint().z);
			this->vertices_hand.push_back(finger_joint);
		}
	}
}

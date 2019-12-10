#include <iostream>
#include "./finger_joints.h"

using namespace std;

int main()
{
	Hands hand;
	while(1) {
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

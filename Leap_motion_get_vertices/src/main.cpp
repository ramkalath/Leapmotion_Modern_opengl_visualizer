/*****************************************************************************
 * Author : Ram
 * Date :  19/12/19
 * Email : ramkalath@gmail.com
 * Breif Description : leap motion joint info print on the screen
 * Detailed Description :
 *****************************************************************************/

#include <iostream>
#include "./finger_joints.h"
int main()
{
	Hands hand;
	while(1) {
		if(hand.detect_hands())
		{
			for(unsigned long i=0; i<hand.vertices_hand.size(); i++)
			{
				std::cout << "joint " << i << "\t"
						  << hand.vertices_hand[i].x << "\t"
						  << hand.vertices_hand[i].y << "\t"
						  << hand.vertices_hand[i].z << std::endl;
			}
		}
		std::cout << "-------------------------------------" << std::endl;
	}

    return 0;
}

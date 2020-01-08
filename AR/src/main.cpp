/*****************************************************************************
* Filename : main.cpp
* Date : 21-12-2019
* Author : Ram
* Email : ramkalath@gmail.com
* Breif Description :
* Detailed Description :
*****************************************************************************/
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/aruco.hpp>

int main()
{
	//cv::Mat image;
	//image = cv::imread("/home/ram/Pictures/amma.jpg");

	//cv::imshow("", image);
	//cv::waitKey();

	cv::Mat markerImage;
	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
	cv::aruco::drawMarker(dictionary, 23, 200, markerImage, 1);
	cv::imshow("", markerImage);
	cv::waitKey();

	return 0;
}

//
//  jeje.cpp
//  Lab 1
//
//  Created by Jesús Jiménez Sánchez on 27/11/17.
//  Copyright © 2017 Jesús Jiménez Sánchez. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int max(int first, int second, int third){
	int max = first;

	if(second > max){
		max = second;
	}

	if(third > max){
		max = third;
	}

	return max;
}

int min(int first, int second, int third){
	int min = first;

	if(second < min){
		min = second;
	}

	if(third < min){
		min = third;
	}

	return min;
}

float min(float first, float second, float third){
	float min = first;

	if(second < min){
		min = second;
	}

	if(third < min){
		min = third;
	}

	return min;
}

float getH(Vec3b color){
	float angle = acos((((float)color[2] - (float)color[1]) + ((float)color[2] - (float)color[0])) / (2 * sqrt(((float)color[2] - (float)color[1]) * ((float)color[2] - (float)color[1]) + ((float)color[2] - (float)color[0]) * ((float)color[1] - (float)color[0]))));
	float H = ((float)color[0] <= (float)color[1]) ? angle : (360 - angle);

	return H;
}

float getS(Vec3b color){
	float S = 1 - ((3 / ((float)color[0] + (float)color[1] + (float)color[2])) * min((float)color[0], (float)color[1], (float)color[2]));

	return S;
}

float getI(Vec3b color){
	float I = (1 / 3) * (color[0] + color[1] + color[2]);

	return I;
}

bool Detection1(Vec3b color){
	bool part1 = (int)color[0] > 20 && (int)color[1] > 40 && (int)color[2] > 95;
	bool part2 = (max((int)color[0], (int)color[1], (int)color[2]) - min((int)color[0], (int)color[1], (int)color[2])) > 15;
	bool part3 = abs((int)color[2] - (int)color[1]) > 15 && (int)color[2] > (int)color[1] && (int)color[2] > (int)color[0];

	return part1 && part2 && part3;
}

bool Detection2(Vec3b color){
	bool part1 = ((float)color[2] / (float)color[1]) > 1.185;
	bool part2 = (((float)color[2] * (float)color[0]) / (((float)color[0] + (float)color[1] + (float)color[2]) * ((float)color[0] + (float)color[1] + (float)color[2]))) > 0.107;
	bool part3 = (((float)color[2] * (float)color[1]) / (((float)color[0] + (float)color[1] + (float)color[2]) * ((float)color[0] + (float)color[1] + (float)color[2]))) > 0.112;

	return part1 && part2 && part3;
}

int main(){
	Mat img[12];
	Vec3b color;
	string windowName;

	// Open the images
	img[0] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/1.jpg");
	img[1] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/2.jpg");
	img[2] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/3.jpg");
	img[3] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/4.jpg");
	img[4] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/5.jpg");
	img[5] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/group.jpg");
	img[6] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/group2.jpg");
	img[7] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/hands3.jpg");
	img[8] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/manwoman.jpg");
	img[9] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/t26.jpg");
	img[10] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/t27.jpg");
	img[11] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 1/Images/t63.jpg");

	// Check if the images were opened right
	for(int i = 0; i < 12; i++){
		if(!img[i].data){
			cout << "Image " << i << " could not be opened" << endl;
		}
	}

	for(int i = 0; i < 12; i++){
		for(int y = 0; y < img[i].rows; y++){
			for(int x = 0; x < img[i].cols; x++){
				color = img[i].at<Vec3b>(Point(x, y));

				/*
					0 --> B
					1 --> G
					2 --> R
				*/
				if(Detection2(color)){
					color[0] = 0;
					color[1] = 0;
					color[2] = 255;
				}

				img[i].at<Vec3b>(Point(x, y)) = color;
			}
		}
	}

	for(int i = 0; i < 12; i++){
		windowName = "Image " + to_string(i);

		namedWindow(windowName, WINDOW_AUTOSIZE);	// Create a window for display.
		imshow(windowName, img[i]);				// Show our image inside it.
	}
	
	waitKey(0);									// Wait for a keystroke in the window
}

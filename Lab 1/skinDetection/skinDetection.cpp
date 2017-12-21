//
//  skinDetection.cpp
//  Lab 1
//
//  Created by Jesús Jiménez Sánchez on 27/11/17.
//  Copyright © 2017 Jesús Jiménez Sánchez. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

// Global variables
string face_cascade_name = "../../haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
string window_name = "Capture - Face detection";
int filenumber; // Number of file to be saved
string filename;

/*
	Functions to get max and min values
*/
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

/*
	Functions to get HSI values from RGB
*/
float getH(Vec3b color){
	float angle = acos((((float)color[2] - (float)color[1]) + ((float)color[2] - (float)color[0])) / (2 * sqrt(((float)color[2] - (float)color[1]) * ((float)color[2] - (float)color[1]) + ((float)color[2] - (float)color[0]) * ((float)color[1] - (float)color[0]))));
	float H = ((float)color[0] <= (float)color[1]) ? angle : (360.0 - angle);

	return H;
}

float getS(Vec3b color){
	float S = 1.0 - ((3.0 / ((float)color[0] + (float)color[1] + (float)color[2])) * min((float)color[0], (float)color[1], (float)color[2]));

	return S;
}

float getI(Vec3b color){
	float I = (1.0 / 3.0) * ((float)color[0] + (float)color[1] + (float)color[2]);

	return I;
}

/*
	Functions to get YCbCr from RGB
	Method found at http://www.equasys.de/colorconversion.html
*/
vector< vector<float> > conversionMatrix(){
	vector< vector<float> > matrix(3);

	matrix[0].reserve(3);
	matrix[1].reserve(3);
	matrix[2].reserve(3);

	matrix[0][0] = 0.299;
	matrix[0][1] = 0.587;
	matrix[0][2] = 0.114;
	matrix[1][0] = -0.169;
	matrix[1][1] = -0.331;
	matrix[1][2] = 0.500;
	matrix[2][0] = 0.500;
	matrix[2][1] = -0.419;
	matrix[2][2] = -0.081;

	return matrix;
}

float getY(Vec3b color){
	//return 16 + (65.481 * (float)color[2] + 128.553 * (float)color[1] + 24.966 * (float)color[0]) / 255;
	vector< vector<float> > matrix = conversionMatrix();

	return matrix[0][0] * color[2] + matrix[0][1] * color[1] + matrix[0][2] * color[0];
}

float getCb(Vec3b color){
	//return 128 + (-37.797 * (float)color[2] - 74.203 * (float)color[1] + 112.0 * (float)color[0]) / 255;
	vector< vector<float> > matrix = conversionMatrix();

	return 128 + (matrix[1][0] * color[2] + matrix[1][1] * color[1] + matrix[1][2] * color[0]);
}

float getCr(Vec3b color){
	//return 128 + (128.0 * (float)color[2] - 93.786 * (float)color[1] - 18.214 * (float)color[0]) / 255;
	vector< vector<float> > matrix = conversionMatrix();

	return 128 + (matrix[2][0] * color[2] + matrix[2][1] * color[1] + matrix[2][2] * color[0]);
}

/*
	Functions to detect skin in different ways
*/
// Based on RGB 
bool Detection1(Vec3b color){
	bool part1 = (int)color[0] > 20 && (int)color[1] > 40 && (int)color[2] > 95;
	bool part2 = (max((int)color[0], (int)color[1], (int)color[2]) - min((int)color[0], (int)color[1], (int)color[2])) > 15;
	bool part3 = abs((int)color[2] - (int)color[1]) > 15 && (int)color[2] > (int)color[1] && (int)color[2] > (int)color[0];

	return part1 && part2 && part3;
}

// Based on RGB
bool Detection2(Vec3b color){
	bool part1 = ((float)color[2] / (float)color[1]) > 1.185;
	bool part2 = (((float)color[2] * (float)color[0]) / (((float)color[0] + (float)color[1] + (float)color[2]) * ((float)color[0] + (float)color[1] + (float)color[2]))) > 0.107;
	bool part3 = (((float)color[2] * (float)color[1]) / (((float)color[0] + (float)color[1] + (float)color[2]) * ((float)color[0] + (float)color[1] + (float)color[2]))) > 0.112;

	return part1 && part2 && part3;
}

// Based on HSI
bool Detection3(Vec3b color){
	bool part1 = getI(color) >= 0.4;
	bool part2 = 0.2 < getS(color) && getS(color) > 0.6;
	bool part3 = (0 < getH(color) && getH(color) < 25) || (335 < getH(color) && getH(color) <= 360);

	return part1 && part2 && part3;
}

// Based on HSI
bool Detection4(Vec3b color){
	bool part1 = 0 < getH(color) && getH(color) < 50;
	bool part2 = 0.23 < getS(color) && getS(color) < 0.68;

	return part1 && part2;
}

// Based on HSI
bool Detection5(Vec3b color){
	bool part1 = getS(color) >= 10 && getI(color) >= 20 && getS(color) <= (110 - getH(color) - (0.1 * getI(color)));
	bool part2 = getH(color) <= (75 - (0.4 * getI(color)));

	return part1 || part2;
}

// Based on YCbCr
bool Detection6(Vec3b color){
	bool part1 = getY(color) > 80 && 85 < getCb(color) && getCb(color) < 135 && 135 < getCr(color) && getCr(color) < 180;
	bool part2 = (0 < getY(color) && getY(color) < 255) && (0 < getCb(color) && getCb(color) < 255) && (0 < getCr(color) && getCr(color) < 255);

	return part1 && part2;
}

bool Detection7(Vec3b color){
	bool part1 = 80 <= getCb(color) && getCb(color) <= 120;
	bool part2 = 133 <= getCr(color) && getCr(color) <= 173;

	return part1 && part2;
}

// Function detectAndDisplay
void detectAndDisplay(Mat frame){
	vector<Rect> faces;
	Mat frame_gray;
	Mat crop;
	Mat res;
	Mat gray;
	string text;
	stringstream sstm;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	// Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	// Set Region of Interest
	Rect roi_b;
	Rect roi_c;

	size_t ic = 0; // ic is index of current element
	int ac = 0; // ac is area of current element

	size_t ib = 0; // ib is index of biggest element
	int ab = 0; // ab is area of biggest element

	for (ic = 0; ic < faces.size(); ic++){ // Iterate through all current elements (detected faces){
		roi_c.x = faces[ic].x;
		roi_c.y = faces[ic].y;
		roi_c.width = (faces[ic].width);
		roi_c.height = (faces[ic].height);

		ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

		roi_b.x = faces[ib].x;
		roi_b.y = faces[ib].y;
		roi_b.width = (faces[ib].width);
		roi_b.height = (faces[ib].height);

		ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

		if(ac > ab){
			ib = ic;
			roi_b.x = faces[ib].x;
			roi_b.y = faces[ib].y;
			roi_b.width = (faces[ib].width);
			roi_b.height = (faces[ib].height);
		}

		crop = frame(roi_b);
		resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR); // This will be needed later while saving images
		cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale

		// Form a filename
		// filename = "";
		// stringstream ssfn;
		// ssfn << filenumber << ".png";
		// filename = ssfn.str();
		// filenumber++;

		// imwrite(filename, gray);

		Point pt1(faces[ic].x, faces[ic].y);	// Display detected faces on main window - live stream from camera
		Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
		rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
	}

	// Show image
	// sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
	// text = sstm.str();

	//putText(frame, text, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
	imshow("original", frame);

	if(!crop.empty()){
		imshow("detected", crop);
	}
	else{
		destroyWindow("detected");
	}
}

int main(){
	Mat img[12];
	Vec3b color;
	string windowName;

	// Load the cascade
    if (!face_cascade.load(face_cascade_name)){
        printf("--(!)Error loading\n");
        return (-1);
    }

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

		// Apply the classifier to the frame
		if (!img[i].empty()){
			detectAndDisplay(img[i]);
		}
		else{
			printf(" --(!) No captured frame -- Break!");
			break;
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
				if(Detection7(color)){
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

	// int c = waitKey(10);

	// if (27 == char(c)){
	// 	;
	// }
	
	waitKey(0);									// Wait for a keystroke in the window
}

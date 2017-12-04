/*
	Generation of an emoji designed by myself
*/

#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main(){
    Mat img(500, 500, CV_8UC3, Scalar(255,255, 255));

	// Shape of the face
	circle(img, Point(249, 249), 200.0, Scalar(0, 255, 255), -1, CV_AA);
	circle(img, Point(249, 249), 200.0, Scalar(0, 0, 0), 1, CV_AA);
	
	// Eyes
	//// Left eye
	circle(img, Point(170, 180), 50.0, Scalar(255, 255, 255), -1, CV_AA);
	circle(img, Point(170, 180), 50.0, Scalar(0, 0, 0), 1, CV_AA);
	circle(img, Point(170, 180), 10.0, Scalar(0, 0, 0), -1, CV_AA);

	//// Right eye
	circle(img, Point(328, 180), 50.0, Scalar(255, 255, 255), -1, CV_AA);
	circle(img, Point(328, 180), 50.0, Scalar(0, 0, 0), 1, CV_AA);
	circle(img, Point(328, 180), 10.0, Scalar(0, 0, 0), -1, CV_AA);

	// Mouth
	ellipse(img, Point(249, 350), Size(40.0, 70.0), 90, 0, 360, Scalar(0, 0, 0), -1, CV_AA);
	// line(img, Point(200, 370), Point(298, 370), Scalar(0, 0, 0), 3, CV_AA);

	// Rouge
	// circle(img, Point(140, 310), 40.0, Scalar(132, 17, 255), -1, CV_AA);
	// circle(img, Point(358, 310), 40.0, Scalar(132, 17, 255), -1, CV_AA);

	// line(img, Point(249, 0), Point(249, 499), Scalar(0, 0, 0), 1, CV_AA);
	// line(img, Point(0, 249), Point(499, 249), Scalar(0, 0, 0), 1, CV_AA);

	// Display image (and save)
	namedWindow("emoji", WINDOW_AUTOSIZE);	// Create a window for display.
	imshow("emoji", img);				// Show our image inside it.
	imwrite("emoji.png", img);			// Save image

	
	waitKey(0);									// Wait for a keystroke in the window
}
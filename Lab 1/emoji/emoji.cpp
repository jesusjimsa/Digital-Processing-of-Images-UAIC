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
	// To create an image
    // CV_8UC3 depicts : (3 channels,8 bit image depth
    // Height  = 500 pixels, Width = 1000 pixels
    // (0, 0, 100) assigned for Blue, Green and Red 
    //             plane respectively. 
    // So the image will appear red as the red 
    // component is set to 100.
    Mat img(500, 500, CV_8UC3, Scalar(255,255, 255));

	namedWindow("emoji", WINDOW_AUTOSIZE);	// Create a window for display.
	imshow("emoji", img);				// Show our image inside it.

	
	waitKey(0);									// Wait for a keystroke in the window
}
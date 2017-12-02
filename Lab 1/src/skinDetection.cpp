//
//  jeje.cpp
//  Lab 1
//
//  Created by Jesús Jiménez Sánchez on 27/11/17.
//  Copyright © 2017 Jesús Jiménez Sánchez. All rights reserved.
//

#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main(){
	Mat img[12];
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
		windowName = "Image " + to_string(i);

		namedWindow(windowName, WINDOW_AUTOSIZE);	// Create a window for display.
		imshow(windowName, img[i]);				// Show our image inside it.
	}
	
	waitKey(0);									// Wait for a keystroke in the window
}

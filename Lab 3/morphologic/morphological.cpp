#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main(){
	Mat img[4];
	Mat ERelementRECT, ERelementELL, ERelementCROSS, DILelementRECT, DILelementELL, DILelementCROSS;
	Mat erodedRECT, erodedELL, erodedCROSS, dilatedRECT, dilatedELL, dilatedCROSS;
	string windowName;
	int erosion_size = 1;
	int dilation_size = 1;

	img[0] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 3/Images/basic_shapes.png");
	img[1] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 3/Images/DIP_GW_page.tif");
	img[2] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 3/Images/patrat_cu_pete.tif");
	img[3] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 3/Images/shapes.png");

	// Check if the images were opened right
	for(int i = 0; i < 4; i++){
		if(!img[i].data){
			cout << "Image " << i << " could not be opened" << endl;
		}
	}

	//Erosion
	ERelementRECT = getStructuringElement(MORPH_RECT, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
	ERelementELL = getStructuringElement(MORPH_ELLIPSE, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
	ERelementCROSS = getStructuringElement(MORPH_CROSS, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
	erode(img[1], erodedRECT, ERelementRECT);
	erode(img[1], erodedELL, ERelementELL);
	erode(img[1], erodedCROSS, ERelementCROSS);

	//Dilation
	DILelementRECT = getStructuringElement(MORPH_RECT, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
	DILelementELL = getStructuringElement(MORPH_ELLIPSE, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
	DILelementCROSS = getStructuringElement(MORPH_CROSS, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
	erode(img[1], dilatedRECT, DILelementRECT);
	erode(img[1], dilatedELL, DILelementELL);
	erode(img[1], dilatedCROSS, DILelementCROSS);

	for(int i = 0; i < 4; i++){
		windowName = "Image " + to_string(i);
		
		if(i == 1){
			namedWindow(windowName, WINDOW_AUTOSIZE);	// Create a window for display.
			imshow(windowName, img[i]);				// Show our image inside it.
		}
	}

	namedWindow("erodedRECT", WINDOW_AUTOSIZE);
	imshow("erodedRECT", erodedRECT);

	namedWindow("erodedELL", WINDOW_AUTOSIZE);
	imshow("erodedELL", erodedELL);

	namedWindow("erodedCROSS", WINDOW_AUTOSIZE);
	imshow("erodedCROSS", erodedCROSS);


	namedWindow("dilatedRECT", WINDOW_AUTOSIZE);
	imshow("dilatedRECT.png", dilatedRECT);

	namedWindow("dilatedELL", WINDOW_AUTOSIZE);
	imshow("dilatedELL.png", dilatedELL);

	namedWindow("dilatedCROSS", WINDOW_AUTOSIZE);
	imshow("dilatedCROSS.png", dilatedCROSS);
	
	
	waitKey(0);									// Wait for a keystroke in the window
}
#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main(){
	Mat img[4];
	string windowName;
	Mat ERelementRECT, ERelementELL, ERelementCROSS, DILelementRECT, DILelementELL, DILelementCROSS;
	Mat erodedRECT, erodedELL, erodedCROSS, dilatedRECT, dilatedELL, dilatedCROSS;
	Mat fixed, patrat;
	int morph_size = 1;
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1 ), Point(morph_size, morph_size));
	int erosion_size = 6;
	int dilation_size = 10;

	img[0] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 3/Images/basic_shapes.png");
	img[1] = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 3/Images/DIP_GW_page.tif");
	patrat = imread("/Users/jesusjimsa/Dropbox/Documentos/Universidad/3 - Primer cuatrimestre/Digital Processing of Images/Prácticas/Digital-Processing-of-Images-UAIC/Lab 3/Images/patrat_cu_pete.tif");
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
	dilate(img[1], dilatedRECT, DILelementRECT);
	dilate(img[1], dilatedELL, DILelementELL);
	dilate(img[1], dilatedCROSS, DILelementCROSS);

	// Opening and closing
	morphologyEx(img[1], fixed, MORPH_OPEN, element);
	morphologyEx(fixed, fixed, MORPH_CLOSE, element);
	morphologyEx(fixed, fixed, MORPH_OPEN, element);
	morphologyEx(fixed, fixed, MORPH_CLOSE, element);
	morphologyEx(fixed, fixed, MORPH_OPEN, element);
	
	erode(patrat, patrat, ERelementRECT);
	dilate(patrat, patrat, DILelementRECT);
	dilate(patrat, patrat, DILelementRECT);
	erode(patrat, patrat, ERelementRECT);
	erode(patrat, patrat, ERelementRECT);
	// dilate(patrat, patrat, DILelementRECT);
	// dilate(patrat, patrat, DILelementRECT);
	// erode(patrat, patrat, ERelementRECT);
	// erode(patrat, patrat, ERelementRECT);
	// dilate(patrat, patrat, DILelementRECT);
	// erode(patrat, patrat, ERelementRECT);

	namedWindow(windowName, WINDOW_AUTOSIZE);	// Create a window for display.
	imshow(windowName, patrat);


	// MORPH_OPEN
	// MORPH_CLOSE
	// MORPH_HITMISS

	// for(int i = 0; i < 4; i++){
	// 	windowName = "Image " + to_string(i);

	// 	if(i != 1){
	// 		namedWindow(windowName, WINDOW_AUTOSIZE);	// Create a window for display.
	// 		imshow(windowName, img[i]);				// Show our image inside it.
	// 		imwrite("pff.png", img[i]);
	// 	}
	// }

	// namedWindow("erodedRECT", WINDOW_AUTOSIZE);
	// imshow("erodedRECT", erodedRECT);
	// imwrite("erodedRECT.png", erodedRECT);

	// namedWindow("erodedELL", WINDOW_AUTOSIZE);
	// imshow("erodedELL", erodedELL);
	// imwrite("erodedELL.png", erodedELL);

	// namedWindow("erodedCROSS", WINDOW_AUTOSIZE);
	// imshow("erodedCROSS", erodedCROSS);
	// imwrite("erodedCROSS.png", erodedCROSS);

	// namedWindow("dilatedRECT", WINDOW_AUTOSIZE);
	// imshow("dilatedRECT.png", dilatedRECT);
	// imwrite("dilatedRECT.png", dilatedRECT);

	// namedWindow("dilatedELL", WINDOW_AUTOSIZE);
	// imshow("dilatedELL.png", dilatedELL);
	// imwrite("dilatedELL.png", dilatedELL);

	// namedWindow("dilatedCROSS", WINDOW_AUTOSIZE);
	//imshow("dilatedCROSS.png", dilatedCROSS);
	// imwrite("dilatedCROSS.png", dilatedCROSS);

	// namedWindow("fixed", WINDOW_AUTOSIZE);
	// imshow("fixed", fixed);
	// imwrite("fixed.png", fixed);

	waitKey(0);									// Wait for a keystroke in the window
}
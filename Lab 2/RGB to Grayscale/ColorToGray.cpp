/*
	Convert a RGB image to grayscale
*/

#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

/*
	0 --> B
	1 --> G
	2 --> R
*/

/*
	Functions to get max and min values
*/

float max(float first, float second, float third){
	float max = first;

	if(second > max){
		max = second;
	}

	if(third > max){
		max = third;
	}

	return max;
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
	Averaging techniques
*/

Vec3b simpleAveraging(Vec3b color){
	Vec3b gray;

	gray[2] = ((float)color[0] + (float)color[1] + (float)color[2]) / 3.0;
	gray[1] = ((float)color[0] + (float)color[1] + (float)color[2]) / 3.0;
	gray[0] = ((float)color[0] + (float)color[1] + (float)color[2]) / 3.0;

	return gray;
}

Vec3b weightedAverage1(Vec3b color){
	Vec3b gray;

	gray[2] = 0.3 * (float)color[2] + 0.59 * (float)color[1] + 0.11 * (float)color[0];
	gray[1] = 0.3 * (float)color[2] + 0.59 * (float)color[1] + 0.11 * (float)color[0];
	gray[0] = 0.3 * (float)color[2] + 0.59 * (float)color[1] + 0.11 * (float)color[0];

	return gray;
}

Vec3b weightedAverage2(Vec3b color){
	Vec3b gray;
	
	gray[2] = 0.2126 * (float)color[2] + 0.7152 * (float)color[1] + 0.0722 * (float)color[0];
	gray[1] = 0.2126 * (float)color[2] + 0.7152 * (float)color[1] + 0.0722 * (float)color[0];
	gray[0] = 0.2126 * (float)color[2] + 0.7152 * (float)color[1] + 0.0722 * (float)color[0];

	return gray;
}

Vec3b weightedAverage3(Vec3b color){
	Vec3b gray;

	gray[2] = 0.299 * (float)color[2] + 0.587 * (float)color[1] + 0.114 * (float)color[0];
	gray[1] = 0.299 * (float)color[2] + 0.587 * (float)color[1] + 0.114 * (float)color[0];
	gray[0] = 0.299 * (float)color[2] + 0.587 * (float)color[1] + 0.114 * (float)color[0];

	return gray;
}

/*
	Desaturation techique
*/

Vec3b desaturation(Vec3b color){
	Vec3b gray;

	gray[2] = (min((float)color[2], (float)color[1], (float)color[0]) + max((float)color[2], (float)color[1], (float)color[0])) / 2.0;
	gray[1] = (min((float)color[2], (float)color[1], (float)color[0]) + max((float)color[2], (float)color[1], (float)color[0])) / 2.0;
	gray[0] = (min((float)color[2], (float)color[1], (float)color[0]) + max((float)color[2], (float)color[1], (float)color[0])) / 2.0;

	return gray;
}

/*
	Decomposition techniques
*/

Vec3b decompositionMax(Vec3b color){
	Vec3b gray;

	gray[2] = max((float)color[2], (float)color[1], (float)color[0]);
	gray[1] = max((float)color[2], (float)color[1], (float)color[0]);
	gray[0] = max((float)color[2], (float)color[1], (float)color[0]);

	return gray;
}

Vec3b decompositionMin(Vec3b color){
	Vec3b gray;

	gray[2] = min((float)color[2], (float)color[1], (float)color[0]);
	gray[1] = min((float)color[2], (float)color[1], (float)color[0]);
	gray[0] = min((float)color[2], (float)color[1], (float)color[0]);

	return gray;
}

/*
	One color techniques
*/

Vec3b singleR(Vec3b color){
	Vec3b gray;

	gray[2] = color[2];
	gray[1] = 0;
	gray[0] = 0;

	return gray;
}

Vec3b singleG(Vec3b color){
	Vec3b gray;

	gray[2] = 0;
	gray[1] = color[1];
	gray[0] = 0;

	return gray;
}

Vec3b singleB(Vec3b color){
	Vec3b gray;

	gray[2] = 0;
	gray[1] = 0;
	gray[0] = color[0];

	return gray;
}

/*
	Functions for choosing values depending on the position in the interval
*/
float intervals16(float value){
	if(0 <= value && value < 16){
		value = 8;
	}
	else{
		if(16 <= value && value < 32){
			value = 24;
		}
		else{
			if(32 <= value && value < 48){
				value = 40;
			}
			else{
				if(48 <= value && value < 64){
					value = 56;
				}
				else{
					if(64 <= value && value < 80){
						value = 72;
					}
					else{
						if(80 <= value && value < 96){
							value = 88;
						}
						else{
							if(96 <= value && value < 112){
								value = 104;
							}
							else{
								if(112 <= value && value < 128){
									value = 120;
								}
								else{
									if(128 <= value && value < 144){
										value = 136;
									}
									else{
										if(144 <= value && value < 160){
											value = 152;
										}
										else{
											if(160 <= value && value < 176){
												value = 168;
											}
											else{
												if(176 <= value && value < 192){
													value = 184;
												}
												else{
													if(192 <= value && value < 208){
														value = 200;
													}
													else{
														if(208 <= value && value < 224){
															value = 216;
														}
														else{
															if(224 <= value && value < 240){
																value = 232;
															}
															else{
																if(240 <= value && value < 256){
																	value = 248;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return value;
}

float intervals2(float value){
	if(value <= 128){
		value = 0;
	}
	else{
		value = 255;
	}

	return value;
}

/*
	Gray scale based on interval technique
*/

Vec3b grayShades(Vec3b color){
	Vec3b gray;
	Vec3b weighted = weightedAverage3(color);

	gray[2] = intervals16((float)weighted[2]);
	gray[1] = intervals16((float)weighted[1]);
	gray[0] = intervals16((float)weighted[0]);

	return gray;
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

				img[i].at<Vec3b>(Point(x, y)) = grayShades(color);
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
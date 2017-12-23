#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

void readAndOpenPaths(vector<string> &pathsARR, vector<string> &pathsFeret, vector<Mat> &ARR, vector<Mat> &Feret){
	fstream ARRText, FeretText;
	string line;
	Mat image;

	ARRText.open("path_to_the_facesARR.txt");
	FeretText.open("path_to_the_facesFeret.txt");

	// Parse files with all the faces
	while(getline(ARRText, line)){
		pathsARR.push_back(line);
	}

	while(getline(FeretText, line)){
		pathsFeret.push_back(line);
	}

	ARRText.close();
	FeretText.close();

	for(int i = 0; i < pathsARR.size(); i++){
		image = imread(pathsARR[i]);

		if(!image.data){
			cout << "Could not open one of the imagesA" << endl;
			cout << "This one --> " << pathsARR[i] << endl;
		}

		ARR.push_back(image);
	}

	for(int i = 0; i < pathsFeret.size(); i++){
		image = imread(pathsFeret[i]);

		if(!image.data){
			cout << "Could not open one of the imagesF" << endl;
			cout << "This one --> " << pathsFeret[i] << endl;
		}

		Feret.push_back(image);
	}
}

int main(){
	vector<string> pathsARR;
	vector<string> pathsFeret;
	vector<Mat> ARR, Feret;

	readAndOpenPaths(pathsARR, pathsFeret, ARR, Feret);

	pathsARR.clear();
	pathsFeret.clear();
	ARR.clear();
	Feret.clear();
}
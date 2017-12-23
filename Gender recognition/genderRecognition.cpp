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

int main(){
	vector<string> pathsARR;
	vector<string> pathsFeret;
	fstream ARRText, FeretText;
	string dePaso;

	ARRText.open("path_to_the_facesARR.txt");
	FeretText.open("path_to_the_facesFeret.txt");

	// Parse files with all the faces
	while(getline(ARRText, dePaso)){
		pathsARR.push_back(dePaso);
	}

	while(getline(FeretText, dePaso)){
		pathsFeret.push_back(dePaso);
	}

	ARRText.close();
	FeretText.close();
	
}
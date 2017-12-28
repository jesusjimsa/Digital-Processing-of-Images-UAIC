#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/contrib/contrib.hpp"

using namespace std;
using namespace cv;

void readAndOpenPaths(vector<string> &pathsARR, vector<string> &pathsFeret, vector<int> &labelsARR, vector<int> &labelsFeret, vector<Mat> &ARR, vector<Mat> &Feret){
	fstream ARRText, FeretText;
	string line;
	Mat image;
	bool pathTime = true;
	int label = -1;

	ARRText.open("path_to_the_facesARR.txt");
	FeretText.open("path_to_the_facesFeret.txt");

	// Parse files with all the faces
	while(getline(ARRText, line)){
		if(pathTime){
			pathsARR.push_back(line);
			pathTime = false;
		}
		else{
			label = stoi(line);
			labelsARR.push_back(label);
			pathTime = true;
		}
	}

	pathTime = true;

	while(getline(FeretText, line)){
		if(pathTime){
			pathsFeret.push_back(line);
			pathTime = false;
		}
		else{
			label = stoi(line);
			labelsFeret.push_back(label);
			pathTime = true;
		}
	}

	ARRText.close();
	FeretText.close();

	cout << "Guardando fotos ARR" << endl;
	for(int i = 0; i < pathsARR.size(); i++){
		image = imread(pathsARR[i], CV_LOAD_IMAGE_GRAYSCALE);

		if(!image.data){
			cout << "Could not open one of the imagesA" << endl;
			cout << "This one --> " << pathsARR[i] << endl;
		}

		ARR.push_back(image);
	}

	cout << "Guardando fotos Feret" << endl;
	for(int i = 0; i < pathsFeret.size(); i++){
		image = imread(pathsFeret[i], CV_LOAD_IMAGE_GRAYSCALE);

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
	vector<int> labelsARR, labelsFeret;
	vector<Mat> ARR, Feret;
	vector<int> labelARR, labelFeret;
	string windowName;
	int heightARR, heightFeret;

	readAndOpenPaths(pathsARR, pathsFeret, labelsARR, labelsFeret, ARR, Feret);

	/*
		We'll need this later in code to reshape the
		images to their original size
	*/
	heightARR = ARR[0].rows;
	//heightFeret = Feret[0].rows;

	/*
		This is done, so that the training data and the
		test data we test the model with, do not overlap
	*/
	Mat testSample = ARR[ARR.size() - 1];
	int testLabel = labelsARR[labelsARR.size() - 1];
	ARR.pop_back();
	labelsARR.pop_back();

	/*
		The following lines create an Fisherfaces model for
		face recognition and train it with the images and
		labels read from the given text file.
	*/
	cout << "Entrenando el sistema" << endl;
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	model->train(ARR, labelsARR);

	/*
		The following line predicts the label of a given
		test image:
	*/
	cout << "Prediciendo el ejemplo" << endl;
	int predictedLabel = model->predict(testSample);

	if(predictedLabel == 1){
		cout << "Hombre" << endl;
	}
	else{
		cout << "Mujer" << endl;
	}

	pathsARR.clear();
	pathsFeret.clear();
	ARR.clear();
	Feret.clear();
}
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

// Global variables
string face_cascade_name = "../../haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;

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

	cout << "Saving ARR" << endl;
	for(int i = 0; i < pathsARR.size(); i++){
		image = imread(pathsARR[i], CV_LOAD_IMAGE_GRAYSCALE);

		if(!image.data){
			cout << "Could not open one of the imagesA" << endl;
			cout << "This one --> " << pathsARR[i] << endl;
		}

		ARR.push_back(image);
	}

	cout << "Saving Feret" << endl;
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
	string recognised;	
	int heightCrop, widthCrop, xCrop, yCrop;
	int predictedLabel;
	double success;
	double percentage = 0.0;
	
	readAndOpenPaths(pathsARR, pathsFeret, labelsARR, labelsFeret, ARR, Feret);

	/*
		We get the height of Feret images because they are
		smaller than ARR images and we will need to crop
		them to be able to pass Feret images and calculate
		a success percentage.
	*/
	heightCrop = Feret[0].rows;
	widthCrop = Feret[0].cols;
	xCrop = 270;
	yCrop = 66;

	/*
		Now, the ARR images are resized
	*/

	// for(int i = 0; i < ARR.size(); i++){
	// 	resize(ARR[i], ARR[i], Feret[0].size());
	// }

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
	cout << "Training the system with ARR" << endl;
	Ptr<FaceRecognizer> modelARR = createFisherFaceRecognizer();
	modelARR->train(ARR, labelsARR);

	// cout << "Training the system with Feret" << endl;
	// Ptr<FaceRecognizer> modelFeret = createFisherFaceRecognizer();
	// modelFeret->train(Feret, labelsFeret);

	/*
		The following line predicts the label of a given
		test image:
	*/
	cout << "Predicting" << endl;
	predictedLabel = modelARR->predict(testSample);
	recognised = (predictedLabel == 1) ? "Man" : "Woman";

	cout << "Recognised: " << recognised << endl;

	/*
		Calculation of the success ratio
	*/
	// cout << "Calculating success ratio in Feret" << endl;
	// success = 0.0;

	// for(int i = 0; i < Feret.size(); i++){
	// 	predictedLabel = modelARR->predict(Feret[i]);

	// 	if(predictedLabel == labelsFeret[i]){
	// 		success += 1.0;
	// 	}
	// 	else{
	// 		success -= 1.0;
	// 	}
	// }

	// if(success > 0){
	// 	percentage = (success / Feret.size()) * 100;
	// }

	// cout << "Success percentage while recognising Feret images --> " << percentage << "%" << endl;

	// cout << "Calculating success ratio in ARR" << endl;
	// success = 0.0;

	// for(int i = 0; i < ARR.size(); i++){
	// 	predictedLabel = modelFeret->predict(ARR[i]);

	// 	if(predictedLabel == labelsARR[i]){
	// 		success += 1.0;
	// 	}
	// 	else{
	// 		success -= 1.0;
	// 	}
	// }

	// if(success > 0){
	// 	percentage = (success / ARR.size()) * 100;
	// }

	// cout << "Success percentage while recognising ARR images --> " << percentage << "%" << endl;

	pathsARR.clear();
	pathsFeret.clear();
	ARR.clear();
	Feret.clear();
}
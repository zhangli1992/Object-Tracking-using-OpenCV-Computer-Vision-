//motion-Tracking2.cpp

//Written by  Mosam Dabhi

#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace std;
using namespace cv;

const static int SENSITIVITY_VALUE = 20;   //i will get it through trial and error
const static int BLUR_SIZE = 10;  //like we used in SENSITIVITY VALUE


int theObject[2] = { 0, 0 };  //bounding rectangle of the object, we will use the center of this as its position.

Rect objectBoundingRectangle = Rect(0, 0, 0, 0);


string intToString(int number){

	std::stringstream ss;
	ss << number;
	return ss.str();
}

void searchForMovement(Mat thresholdImage, Mat &cameraFeed){
	bool objectDetected = false;
	Mat temp;
	thresholdImage.copyTo(temp);
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(temp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);// retrieves external contours

	if (contours.size()>0)objectDetected = true;
	else objectDetected = false;

	if (objectDetected){
		vector< vector<Point> > largestContourVec;
		largestContourVec.push_back(contours.at(contours.size() - 1));
		objectBoundingRectangle = boundingRect(largestContourVec.at(0));
		int xpos = objectBoundingRectangle.x + objectBoundingRectangle.width / 2;
		int ypos = objectBoundingRectangle.y + objectBoundingRectangle.height / 2;

		//update the objects positions by changing the 'theObject' array values
		theObject[0] = xpos, theObject[1] = ypos;
	}
	int x = theObject[0];
	int y = theObject[1];

	circle(cameraFeed, Point(x, y), 20, Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);

	putText(cameraFeed, "Tracking object at (" + intToString(x) + "," + intToString(y) + ")", Point(x, y), 1, 1, Scalar(255, 0, 0), 2);



}
int main(){

	bool objectDetected = false;
	bool debugMode = false;
	bool trackingEnabled = false;
	bool pause = false;
	Mat frame1, frame2;
	Mat grayImage1, grayImage2;
	Mat differenceImage;
	Mat thresholdImage;
	VideoCapture capture;

	while (1){


		capture.open(0);

		if (!capture.isOpened()){
			cout << "ERROR ACQUIRING VIDEO FEED\n";
			getchar();
			return -1;
		}

		while (capture.get(CV_CAP_PROP_POS_FRAMES)<capture.get(CV_CAP_PROP_FRAME_COUNT) - 1){

			capture.read(frame1);
			cv::cvtColor(frame1, grayImage1, COLOR_BGR2GRAY);
			capture.read(frame2);
			cv::cvtColor(frame2, grayImage2, COLOR_BGR2GRAY);
			cv::absdiff(grayImage1, grayImage2, differenceImage);
			cv::threshold(differenceImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);
			if (debugMode == true){
				cv::imshow("Difference Image", differenceImage);
				cv::imshow("Threshold Image", thresholdImage);
			}
			else{
				cv::destroyWindow("Difference Image");
				cv::destroyWindow("Threshold Image");
			}
			cv::blur(thresholdImage, thresholdImage, cv::Size(BLUR_SIZE, BLUR_SIZE));
			cv::threshold(thresholdImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);
			if (debugMode == true){

				imshow("Final Threshold Image", thresholdImage);

			}
			else {
				cv::destroyWindow("Final Threshold Image");
			}

			if (trackingEnabled){

				searchForMovement(thresholdImage, frame1);
			}

			imshow("Frame1", frame1);
			switch (waitKey(10)){

			case 27: //'esc' key has been pressed, exit program.
				return 0;
			case 116: //'t' has been pressed. this will toggle tracking
				trackingEnabled = !trackingEnabled;
				if (trackingEnabled == false) cout << "Tracking disabled." << endl;
				else cout << "Tracking enabled." << endl;
				break;
			case 100: //'d' has been pressed. this will debug mode
				debugMode = !debugMode;
				if (debugMode == false) cout << "Debug mode disabled." << endl;
				else cout << "Debug mode enabled." << endl;
				break;
			case 112: //'p' has been pressed. this will pause/resume the code.
				pause = !pause;
				if (pause == true){
					cout << "Code paused, press 'p' again to resume" << endl;
					while (pause == true){
						switch (waitKey()){
						case 112:
							pause = false;
							cout << "Code Resumed" << endl;
							break;
						}
					}
				}



			}
		}
		capture.release();
	}

	return 0;

}

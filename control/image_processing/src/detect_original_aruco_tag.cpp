 #include <ros/ros.h>
 #include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
 #include <cv_bridge/cv_bridge.h>
 #include <sstream> // for converting the command line parameter to integer
 #include <opencv2/aruco.hpp>

 using namespace std;
 using namespace cv;

 int main(int argc, char** argv)
 {
   Mat frame;
//--- INITIALIZE VIDEOCAPTURE
VideoCapture cap;
// open the default camera using default API
// cap.open(0);
// OR advance usage: select any API backend
int deviceID = 1;             // 0 = open default camera
int apiID = cv::CAP_ANY;      // 0 = autodetect default API
// open selected camera using selected API
cap.open(deviceID + apiID);
// check if we succeeded
if (!cap.isOpened()) {
    cerr << "ERROR! Unable to open camera\n";
    return -1;
}
//--- GRAB AND WRITE LOOP
cout << "Start grabbing" << endl
    << "Press any key to terminate" << endl;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_ARUCO_ORIGINAL);
while (1)
{
    // wait for a new frame from camera and store it into 'frame'
    cap.read(frame);
            cvtColor(frame, frame, CV_RGB2GRAY);
            Mat normalizedImg;
            //GaussianBlur( frame, frame, Size( 9, 9 ), 0, 0 );
            cv::normalize(frame,  normalizedImg, 0, 100, cv::NORM_MINMAX);
            cv::Mat image, imageCopy;
    normalizedImg.copyTo(imageCopy);
std::vector<int> ids;
std::vector<std::vector<cv::Point2f> > corners;
cv::aruco::detectMarkers(frame, dictionary, corners, ids);
// if at least one marker detected
if (ids.size() > 0)
    cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
    cv::imshow("out", imageCopy);
char key = (char) cv::waitKey(1);
if (key == 27)
    break;
}
// the camera will be deinitialized automatically in VideoCapture destructor
return 0;
}

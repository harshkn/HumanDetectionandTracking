#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;



int main( int argc, char** argv )
{
    VideoCapture cap("TownCentreXVID.mp4");
    // CvCapture cap = cvCreateFileCapture("TownCentreXVID.avi");


    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the video file" << endl;
         return -1;
    }
    double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

    cout << "Frame per seconds : " << fps << endl;

    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"


    while(1)
    {
        Mat img;

        bool bSuccess = cap.read(img); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
                        cout << "Cannot read the frame from video file" << endl;
                       break;
        }

        


    cvtColor(img, img, CV_RGB2GRAY);

    HOGDescriptor hog;

    
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    vector<Rect> found, found_filtered;
    hog.detectMultiScale(img, found, 0, Size(8,8), Size(128,128), 1.05, 2);

    size_t i, j;
        for (i=0; i<found.size(); i++)
        {
            Rect r = found[i];
            for (j=0; j<found.size(); j++)
                if (j!=i && (r & found[j])==r)
                    break;
            if (j==found.size())
                found_filtered.push_back(r);
        }
        for (i=0; i<found_filtered.size(); i++)
        {
            Rect r = found_filtered[i];
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.06);
            r.height = cvRound(r.height*0.9);
            rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 2);
        }
        
    imshow("MyVideo", img); //show the frame in "MyVideo" window

        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
       {
                cout << "esc key is pressed by user" << endl; 
                break; 
       }
    }

                                            // Wait for a keystroke in the window
    return 0;
}

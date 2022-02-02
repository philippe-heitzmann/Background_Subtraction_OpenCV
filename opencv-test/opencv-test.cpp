// opencv-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>

//int main()
//{
//    std::cout << "Hello World!\n";
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	Mat image = Mat::zeros(300, 600, CV_8UC3);
//	circle(image, Point(250, 150), 100, Scalar(0, 255, 128), -100);
//	circle(image, Point(350, 150), 100, Scalar(255, 255, 255), -100);
//	imshow("Display Window", image);
//	waitKey(0);
//	return 0;
//}

#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <string>

#include <type_traits>
#include <typeinfo>

#/*   include <cxxabi.h>
#*///endif

//https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
#include <memory>
#include <string>
#include <cstdlib>
#include <typeinfo>


#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"



using namespace cv;
using namespace std;

const char* params
= "{ help h         |           | Print usage }"
"{ input          | vtest.avi | Path to a video or a sequence of image }"
"{ algo           | MOG2      | Background subtraction method (KNN, MOG2) }";


int main(int argc, char* argv[])
{
    CommandLineParser parser(argc, argv, params);
    parser.about("This program shows how to use background subtraction methods provided by "
        " OpenCV. You can process both videos and images.\n");
    if (parser.has("help"))
    {
        //print help information
        parser.printMessage();
    }

    //! [create]
    //create Background Subtractor objects
    Ptr<BackgroundSubtractor> pBackSub;
    if (parser.get<String>("algo") == "MOG2")
        pBackSub = createBackgroundSubtractorMOG2();
    else
        pBackSub = createBackgroundSubtractorKNN();
    //! [create]

    //! [capture]
    VideoCapture capture(samples::findFile(parser.get<String>("input")));
    if (!capture.isOpened()) {
        //error in opening the video input
        cerr << "Unable to open: " << parser.get<String>("input") << endl;
        return 0;
    }
    //! [capture]

    Mat frame, fgMask, outputfgMask;

    while (true) {
        capture >> frame;
        if (frame.empty())
            break;

        //! [apply]
        //update the background model
        pBackSub->apply(frame, fgMask);
        //! [apply]

        //! [display_frame_number]
        //get the frame number and write it on the current frame
        rectangle(frame, cv::Point(10, 2), cv::Point(100, 20),
            cv::Scalar(255, 255, 255), -1);
        stringstream ss;
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
            FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(100, 0, 0));
        //! [display_frame_number]

        //! [show]
        //show the current frame and the fg masks
        imshow("Frame", frame);
        imshow("FG Mask", fgMask);

        ////https://stackoverflow.com/questions/8449378/finding-contours-in-opencv
        ////std::cout << typeid(fgMask).name() << '\n';
        //cv::threshold(fgMask, outputfgMask, 128, 255, cv::THRESH_BINARY);

        ////Find the contours. Use the contourOutput Mat so the original image doesn't get overwritten
        //std::vector<std::vector<cv::Point> > contours;
        //cv::Mat contourOutput = outputfgMask.clone();
        //cv::findContours(contourOutput, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

        //////Draw the contours
        //cv::Mat contourImage(fgMask.size(), CV_8UC3, cv::Scalar(0, 0, 0));
        //cv::Scalar colors[3];
        //colors[0] = cv::Scalar(255, 0, 0);
        //colors[1] = cv::Scalar(0, 255, 0);
        //colors[2] = cv::Scalar(0, 0, 255);
        //for (size_t idx = 0; idx < contours.size(); idx++) {
        //    cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
        //}

        //imshow("Contours", contourImage);
        ////imshow("Binarized Threshold", outputfgMask);
        ///*cvMoveWindow("Contours", 200, 0);
        //cv::waitKey(0);*/

        ////! [show]
        ////string strMytestString("hello world");
        ////cout << strMytestString;

        ////get the input from the keyboard
        //int keyboard = waitKey(30);
        //if (keyboard == 'q' || keyboard == 27)
        //    break;
    }

    return 0;
}

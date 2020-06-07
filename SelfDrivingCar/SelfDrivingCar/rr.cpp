//#include <iostream>
//#include <vector>
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//#include "linefinder.h"
//#include "edge.h"
//
//#define PI 3.1415926
//
//using namespace std;
//
//int main_fff()
//{
//    cv::Mat image;
//    cv::VideoCapture cap("output1.mp4");
//
//    if (!cap.isOpened())
//    {
//        cerr << "에러\n";
//        return -1;
//    }
//
//    while (1)
//    {
//        cap.read(image);
//        if (image.empty()) {
//            cerr << "빈 영상이 캡쳐되었습니다.\n";
//            break;
//        }
//
//        cv::Rect rr = cv::Rect(0, 30, image.cols - 30, image.rows / 2);
//        cv::Mat img_roi(image, rr);
//
//        // Compute Sobel
//        EdgeDetector ed;
//        ed.computeSobel(img_roi);
//
//        // Apply Canny algorithm
//        cv::Mat contours;
//        cv::Canny(img_roi, contours, 125, 350);
//
//        // Create LineFinder instance
//        LineFinder ld;
//
//        // Set probabilistic Hough parameters
//        ld.setLineLengthAndGap(100, 20);
//        //ld.setMinVote(60);
//
//        // Detect lines
//        std::vector<cv::Vec4i> li = ld.findLines(contours);
//
//        // eliminate inconsistent lines
//        ld.removeLinesOfInconsistentOrientations(ed.getOrientation(), 0.4, 0.1);
//
//        // Display the detected line image
//        //image = cv::imread("road.bmp");
//
//        ld.drawDetectedLines(img_roi);
//        cv::namedWindow("Detected Lines (2)", 1);
//        cv::imshow("Detected Lines (2)", img_roi);
//
//        if (cv::waitKey(1) >= 0)
//            break;
//    }
//    return 0;
//}
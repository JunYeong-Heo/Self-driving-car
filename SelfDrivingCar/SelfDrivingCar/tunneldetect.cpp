//#include <iostream>
//#include <cmath>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//
//int main(int argc, char** argv)
//{
//    cv::VideoCapture capture(0);
//
//    if (!capture.isOpened()) {
//        std::cerr << "Cannot open camera" << std::endl;
//        return 0;
//    }
//
//    cv::namedWindow("Webcam", 1);
//
//    while (true) {    
//
//        cv::Mat frame;
//        
//        cv::Mat Roi;
//        cv::Mat temp;
//        
//        bool frame_valid = true;
//
//        cv::Mat yrb;
//        try {
//            capture >> frame;
//
//            cv::cvtColor(frame, yrb, cv::COLOR_BGR2YCrCb);
//            Roi = yrb(cv::Rect(0, 0, yrb.cols, 100)).clone();
//            cv::threshold(Roi, Roi, 127, 255, cv::THRESH_BINARY);
//        }
//        catch (cv::Exception& e) {
//            std::cerr << "Exception occurred. Ignoring frame... " << e.err << std::endl;
//            frame_valid = false;
//        }
//        cv::inRange(Roi, cv::Scalar(0,0,0), cv::Scalar(60,255,255), temp);
//        if (cv::countNonZero(temp) > 50000)
//            cv::putText(frame, "Tunnel", cv::Point(200, 400), 1, 3, cv::Scalar(255, 0, 255), 5);
//        
//        //cv::imshow("temp",temp);
//        if (frame_valid) {
//            try {
//                // print the output
//                cv::imshow("Roi", temp);
//                cv::imshow("Webcam", frame);
//            }
//            catch (cv::Exception& e) {
//                std::cerr << "Exception occurred. Ignoring frame... " << e.err << std::endl;
//            }
//        }
//
//        if (cv::waitKey(30) >= 0) break;
//    }
//
//
//    return 0;
//}
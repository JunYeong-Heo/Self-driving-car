//#pragma once
//
//#include <opencv2/core.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//
//
//using namespace cv;
//using namespace std;
//
//void img_Color_detect(Mat img_original, Mat& img_hsv)
//{
//	Mat result(img_original.rows, img_original.cols, CV_8UC3, Scalar(0, 0, 0));
//
//	cvtColor(img_original, img_hsv, COLOR_BGR2HSV);
//	for (size_t i = 0; i < img_original.rows; i++)
//	{
//		for (size_t j = 0; j < img_original.cols; j++)
//		{
//			if (img_hsv.at<Vec3b>(i, j)[1] <= 255 && img_hsv.at<Vec3b>(i, j)[1] >= 180)
//			{
//			}
//		}
//	}
//}
//int main_ggg(void)
//{
//	Mat frame;
//	VideoCapture cap("output1.mp4");
//
//	int fps = cap.get(CAP_PROP_FPS);
//
//	Mat img_original, img_edge, img_gray;
//
//	if (!cap.isOpened())
//	{
//		cerr << "open err" << endl;
//		return -1;
//	}
//	
//	double iAngle = 90;
//
//	while (1)
//	{
//		cap.read(img_original);
//
//		Rect rr = Rect(0, 30, img_original.cols - 30, img_original.rows / 2);
//		Mat img_roi(img_original, rr);
//
//		cvtColor(img_roi, img_gray, COLOR_BGR2GRAY);
//
//		Canny(img_gray, img_edge, 30, 120, 3);
//
//		vector<Vec4i> lines;
//		HoughLinesP(img_edge, lines, 1, CV_PI / 180, 30, 10, 1);
//
//		Mat img_null(img_edge.rows, img_edge.cols, CV_8UC3, Scalar(0, 0, 0));
//		Mat img_result(img_edge.rows, img_edge.cols, CV_8UC3, Scalar(0, 0, 0));
//
//		int curve = img_original.at<Vec3b>(0, 0)[0];
//		int norm = img_original.at<Vec3b>(0, 0)[1];
//		int theta = img_original.at<Vec3b>(0, 0)[2];
//
//		cout << "line detect : " << lines.size()
//			<< " rho : " << curve << " norm  : " << norm << " theta : " << theta << endl;
//
//		Mat img_hsv;
//
//		for (int i = 0; i < lines.size(); i++)
//		{
//			Vec4i L = lines[i];
//			line(img_null, Point(L[0], L[1]), Point(L[2], L[3]), Scalar(0, 255, 255), 1, LINE_AA);
//		}
//
//		cvtColor(img_roi, img_hsv, COLOR_BGR2HSV);
//		inRange(img_hsv, Scalar(0, 0, 30), Scalar(255, 30, 255), img_result);
//
//		imshow("edge", img_edge);
//		imshow("Line", img_null);
//		imshow("result", img_result);
//		imshow("roi", img_roi);
//
//		imshow("original", img_original);
//
//		int wait = int(1.0 / fps * 25);
//
//		if (waitKey(wait) >= 0)
//			break;
//		//set_intersection()
//	}
//}
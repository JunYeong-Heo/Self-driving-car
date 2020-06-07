//#include <iostream>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//
//using namespace std;
//using namespace cv;
//
//int main_ggggjhjj(void)
//{
//	VideoCapture cap(0);
//
//	cap.set(CAP_PROP_FRAME_WIDTH, 320);
//	cap.set(CAP_PROP_FRAME_HEIGHT, 240);
//
//	Mat img_hsv, img_red;
//	Mat img_red_threshold1, img_red_threshold2;
//	
//	Mat frame;
//
//	for (;;)
//	{
//		cap.read(frame);
//
//		//flip(frame, frame, 1);
//		cvtColor(frame, img_hsv, COLOR_BGR2HSV);
//		
//		inRange(img_hsv, Scalar(0, 30, 0), Scalar(10, 255, 255), img_red_threshold1);
//		inRange(img_hsv, Scalar(170, 30, 0), Scalar(180, 255, 255), img_red_threshold2);
//
//		img_red = img_red_threshold1 | img_red_threshold2;
//
//		cout << "red count" << countNonZero(img_red) << endl;
//
//		if (countNonZero(img_red) > 12000)
//		{
//			vector<Vec3f> circles;
//			Mat img_gray;
//			cvtColor(frame, img_gray, COLOR_BGR2GRAY);
//			cout << "Red Detective" << endl;
//			HoughCircles(img_gray, circles, HOUGH_GRADIENT, 1, 125, 250, 45);
//
//			if (circles.size() == 1 || circles.size() == 2)
//			{
//				Mat dst;
//				cvtColor(img_gray, dst, COLOR_GRAY2BGR);
//				for (Vec3f c : circles)
//				{
//					Point center(cvRound(c[0]), cvRound(c[1]));
//					int radius = cvRound(c[2]);
//					circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
//				}
//				
//				//cout << "circle size : "<< circles.size() << "STOP!!" << endl;
//				putText(frame, "STOP", Point(80, 70), 3, 1, Scalar(0, 0, 0));
//				imshow("dst", dst);
//			}
//		}
//
//		imshow("stop Detect", frame);
//		imshow("red threshold", img_red);
//
//		if (waitKey(3) == 27)
//			break;
//	}
//	return 0;
//}
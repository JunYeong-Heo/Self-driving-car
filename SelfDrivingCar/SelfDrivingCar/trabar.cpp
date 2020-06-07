//#include <iostream>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//
//using namespace std;
//using namespace cv;
//
//void on_level_change(int pos, void* userData)
//{
//	Mat img = *(Mat *)userData;
//	img.setTo(pos * 16);
//	imshow("image", img);
//}
//int main_hhh(void)
//{
//	//Mat img = Mat::zeros(400, 400, CV_8UC1);
//	namedWindow("image");
//
//	createTrackbar("hue", "image", 0, 18);
//	createTrackbar("sat", "image", 0, 16);
//	createTrackbar("val", "image", 0, 16);
//
//	Mat img = imread("traffic.jpg");
//	cvtColor(img, img, COLOR_BGR2HSV);
//	
//	while (1)
//	{
//		int heu = getTrackbarPos("hue", "image") * 10;
//		int sat = getTrackbarPos("sat", "image") * 16;
//		int val = getTrackbarPos("val", "image") * 16;
//
//		imshow("image", img);
//
//		if (waitKey(1) == 27)
//			break;
//	}
//	return 0;
//}
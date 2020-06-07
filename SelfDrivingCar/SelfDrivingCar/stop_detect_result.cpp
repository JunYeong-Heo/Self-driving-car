//#include <opencv2/core.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//
//#define PIXEL_THRESHOLD 12000
//
//using namespace cv;
//using namespace std;
//
//int main_asdfasdfaqsdf() {
//
//	VideoCapture cap(0);
//
//	while (1)
//	{
//		Mat img;
//		cap.read(img);
//
//		//YCrCb이미지로 변경
//
//		Mat YCrCb, mask(img.size(), CV_8U, Scalar(0));
//		cvtColor(img, YCrCb, COLOR_BGR2YCrCb);
//
//		//YCrCb 이미지를 각 채널별로 분리
//		vector<Mat> planes;
//		split(YCrCb, planes);
//
//		int nr = img.rows;
//		int nc = img.cols;
//
//		// 170 < Cr <230, 70 <Cb < 130인 영역만 255로 표시해서 mask 만들기
//		for (int i = 0; i < nr; i++) {
//			uchar* Cr = planes[1].ptr<uchar>(i);
//			uchar* Cb = planes[2].ptr<uchar>(i);
//
//			for (int j = 0; j < nc; j++) {
//				if ((170 < Cr[j] && Cr[j] < 230) && (70 < Cb[j] && Cb[j] < 130))
//					mask.at<uchar>(i, j) = 255;
//			}
//		}
//
//		if (countNonZero(mask) > PIXEL_THRESHOLD)
//		{
//			GaussianBlur(mask, mask, Size(3, 3), 2, 2);
//		
//			vector<Vec3f> circles;
//			HoughCircles(mask, circles, HOUGH_GRADIENT, 1, 125, 250, 25);
//
//			if (circles.size() >= 1 && circles.size() <= 5)
//			{
//				for (int i = 0; i < circles.size(); i++) {
//					Point center((int)(circles[i][0] + 0.5), (int)(circles[i][1] + 0.5));
//					int radius = (int)(circles[i][2]);
//					circle(img, center, radius, Scalar(255, 0, 0), 3);
//				}
//				//cout << "circle size : "<< circles.size() << "STOP!!" << endl;
//				putText(img, "STOP", Point(200, 400), 1, 3, Scalar(255, 0, 255), 5);
//			}
//			
//		}
//		imshow("red", mask);
//		imshow("IMAGE", img);
//		if (waitKey(3) == 27)
//			break;
//	}
//	return 0;
//}
///**
//  @file SelfDrivingCar solution main.cpp
//  @author jun-yeong Heo
//  @date May 19, 2020
//*/
//
////#include "pch.hpp"
////
////using namespace cv;
////using namespace std;
////
////int threshold1 = 50;
//
////Vec3b lower_blue1, upper_blue1, lower_blue2, upper_blue2, lower_blue3, upper_blue3;
////Mat img_color;
//
////void __stdcall mouse_callback(__out int event,__in int x, __in int y, __in int flags, __in void* param)
////{
////	if (event == EVENT_LBUTTONDOWN)
////	{
////		Vec3b color_pixel = img_color.at<Vec3b>(y, x);
////
////		Mat bgr_color = Mat(1, 1, CV_8UC3, color_pixel);
////
////		Mat hsv_color;
////		cvtColor(bgr_color, hsv_color, COLOR_BGR2HSV);
////
////		int hue = hsv_color.at<Vec3b>(0, 0)[0];
////		int saturation = hsv_color.at<Vec3b>(0, 0)[1];
////		int value = hsv_color.at<Vec3b>(0, 0)[2];
////
////		cout << "Heu = " << hue << endl;
////		cout << "Saturation = " << saturation << endl;
////		cout << "Value = " << value << endl;
////
////		if (hue < 10)
////		{
////			cout << "case 1" << endl;
////			lower_blue1 = Vec3b(hue - 10 + 180, threshold1, threshold1);
////			upper_blue1 = Vec3b(180, 255, 255);
////			lower_blue2 = Vec3b(0, threshold1, threshold1);
////			upper_blue2 = Vec3b(hue, 255, 255);
////			lower_blue3 = Vec3b(hue, threshold1, threshold1);
////			upper_blue3 = Vec3b(hue + 10, 255, 255);
////		}
////		else if (hue > 170)
////		{
////			cout << "case 2" << endl;
////			lower_blue1 = Vec3b(hue, threshold1, threshold1);
////			upper_blue1 = Vec3b(180, 255, 255);
////			lower_blue2 = Vec3b(0, threshold1, threshold1);
////			upper_blue2 = Vec3b(hue + 10 - 180, 255, 255);
////			lower_blue3 = Vec3b(hue - 10, threshold1, threshold1);
////			upper_blue3 = Vec3b(hue, 255, 255);
////		}
////		else
////		{
////			cout << "case 3" << endl;
////			lower_blue1 = Vec3b(hue, threshold1, threshold1);
////			upper_blue1 = Vec3b(hue + 10, 255, 255);
////			lower_blue2 = Vec3b(hue - 10, threshold1, threshold1);
////			upper_blue2 = Vec3b(hue, 255, 255);
////			lower_blue3 = Vec3b(hue - 10, threshold1, threshold1);
////			upper_blue3 = Vec3b(hue, 255, 255);
////		}
////
////		cout << "hue = " << hue << endl;
////		cout << "#1 = " << lower_blue1 << "~" << upper_blue1 << endl;
////		cout << "#2 = " << lower_blue2 << "~" << upper_blue2 << endl;
////		cout << "#3 = " << lower_blue3 << "~" << upper_blue3 << endl;
////	}
////}
//int main(int, char**)
//{
//	Mat frame;
//	VideoCapture cap("car_test1.mp4");
//
//	int fps = cap.get(CAP_PROP_FPS);
//
//	Mat img_edge, img_gray;
//
//	if (!cap.isOpened())
//	{
//		cerr << "open err" << endl;
//		return -1;
//	}
//	Mat img_original;
//	double iAngle = 90;
//
//	while (1)
//	{
//
//		cap.read(img_original);
//		if (img_original.empty())
//		{
//			cerr << "cap err" << endl;
//			return -1;
//		}
//		//그레이 스케일 영상으로 변환 한후.  
//		cvtColor(img_original, img_gray, COLOR_BGR2GRAY);
//		//캐니에지를 이용하여 에지 성분을 검출합니다.  
//		Canny(img_gray, img_edge, 30, 90, 3);
//
//		//직선 성분을 검출합니다.  
//		vector<Vec4i> lines;
//		HoughLinesP(img_edge, lines, 1, CV_PI / 180, 30, 30, 3);
//
//		//검출한 직선을 영상에 그려줍니다.  
//		for (int i = 0; i < lines.size(); i++)
//		{
//			Vec4i L = lines[i];
//			line(img_original, Point(L[0], L[1]), Point(L[2], L[3]),
//				Scalar(0, 0, 255), 1, LINE_AA);
//
//			int curve = img_original.at<Vec3b>(0, 0)[0];
//			int norm = img_original.at<Vec3b>(0, 0)[1];
//			int theta = img_original.at<Vec3b>(0, 0)[2];
//
//			cout << "line detect : " << lines.size()
//				<< " rho : " << curve << " norm  : " << norm << " theta : " << theta << endl;
//
//		}
//
//		imgRotate(img_original, iAngle);
//		////영상 돌리기
//		//Mat matRotation = getRotationMatrix2D(Point(img_original.rows / 2, img_original.cols / 2), iAngle - 180, 1);
//		//warpAffine(img_original, img_original, matRotation, img_original.size());
//
//		imgRotate(img_edge, iAngle);
//		//영상 돌리기
//		/*Mat matRotation = getRotationMatrix2D(Point(img_edge.rows / 2, img_edge.cols / 2), iAngle - 180, 1);
//		warpAffine(img_edge, img_edge, matRotation, img_edge.size());*/
//
//		//namedWindow("edge", WINDOW_AUTOSIZE);
//		imshow("edge", img_edge);
//
//		//namedWindow("result", WINDOW_NORMAL);
//		imshow("result", img_original);
//
//		//imshow("line", lines);
//		
//		int wait = int(1.0 / fps * 25);
//		if (waitKey(wait) >= 0)
//			break;
//	}
//
//}
//#include <iostream>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include "pch.hpp"
//
//
//using namespace std;
//using namespace cv;
//
//void setLabel(Mat& image, string str, vector<Point> contour)
//{
//	int fontface = FONT_HERSHEY_SIMPLEX;
//	double scale = 0.5;
//	int thickness = 1;
//	int baseline = 0;
//
//	Size text = getTextSize(str, fontface, scale, thickness, &baseline);
//	Rect r = boundingRect(contour);
//
//	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
//	rectangle(image, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(200, 200, 200), FILLED);
//	putText(image, str, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
//}
//
//int main_asdfasdf(void)
//{
//	namedWindow("dst");
//
//	createTrackbar("hue", "dst", 0, 18);
//	createTrackbar("sat", "dst", 0, 32);
//	createTrackbar("val", "dst", 0, 32);
//
//	VideoCapture cap("trafficLight.mp4");
//
//	/*cap.set(CAP_PROP_FRAME_WIDTH, 320);
//	cap.set(CAP_PROP_FRAME_HEIGHT, 240);*/
//	int fps = cap.get(CAP_PROP_FPS);
//
//	if (!cap.isOpened())
//	{
//		cout << "비디오 오픈 실패" << endl;
//		return -1;
//	}
//
//	Mat frame;
//	Mat img_gray, img_hsv;
//	Mat img_bilateralfilter;
//	Mat img_pro;
//
//	for (;;)
//	{
//
//		cap.read(frame);
//		double sigmaColor = 10.0;
//		double sigmaSpace = 10.0;
//
//		cvtColor(frame, img_hsv, COLOR_BGR2HSV);
//		cvtColor(frame, img_gray, COLOR_BGR2GRAY);
//
//		bilateralFilter(img_gray, img_bilateralfilter, -1, sigmaColor, sigmaSpace);
//		vector<Vec3f> circles;
//		//HoughCircles(img_gray, circles, HOUGH_GRADIENT, 2, 50, 150, 50, 10, 50);
//		//HoughCircles(img_bilateralfilter, circles, HOUGH_GRADIENT, 2, 50, 150, 75, 25, 50);
//
//		//for (int i = 0; i < circles.size(); i++)
//		//{
//		//	cout << "center: " << circles[i][0] << endl;
//		//}//각 원 순서대로 중심점 색 정보 출력
//		//for (Vec3f c : circles)
//		//{
//		//	Point center(cvRound(c[0]), cvRound(c[1]));
//		//	int radius = cvRound(c[2]);
//		//	circle(img_bilateralfilter, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
//		//}
//
//		//inRange(img_hsv, Scalar(Y_H_LOW, Y_S_LOW, 180), Scalar(Y_H_HIGH, Y_S_HIGH, Y_V_HIGH), img_yellow);
//		//int heu = getTrackbarPos("hue", "dst") * 5;
//		int sat = getTrackbarPos("sat", "dst") * 8;
//		//int val = getTrackbarPos("val", "dst");
//
//		inRange(img_hsv, Scalar(0, 0, VALUE_THRESHOLD), Scalar(180, 255, 255), img_pro);
//		
//		int col4s = (img_hsv.cols / 4);
//		int row4s = (img_hsv.rows / 4);
//
//		Rect red = Rect(0, row4s, col4s, 2 * row4s);
//		Rect yellow = Rect(col4s, row4s, col4s, 2 * row4s);
//		Rect left = Rect(2 * col4s, row4s, col4s, 2 * row4s);
//		Rect right = Rect(3 * col4s, row4s, col4s, 2 * row4s);
//
//		Mat img_red(img_pro, red);
//		Mat img_yellow(img_pro, yellow);
//		Mat img_left(img_pro, left);
//		Mat img_right(img_pro, right);
//
//		if (countNonZero(img_red) > 15000)
//			cout << "red!" << endl;
//		if (countNonZero(img_yellow) > 15000)
//			cout << "yellow!" << endl;
//		if (countNonZero(img_left) > 15000)
//			cout << "left!" << endl;
//		if (countNonZero(img_right) > 15000)
//			cout << "right!" << endl;
//
//		//inRange(img_hsv, Scalar(G_H_LOW, G_S_LOW, 180), Scalar(G_H_HIGH, G_S_HIGH, G_V_HIGH), img_green);
//
//		//setroi(img_hsv, img_hsv, Point(240, 640), Point(640, 1080));
//		//imshow("asdf", img_hsv);
//		//cout << "circle size : " << circles.size() << "STOP!!" << endl;
//
//		imshow("dst", img_pro);
//		imshow("origina", frame);
//		//imshow("dst", img_red);
//		//imshow("2", img_yellow);
//		//imshow("3", img_left);
//		//imshow("4", img_right);
//
//
//		//imshow("yellow", img_yellow);
//		//imshow("green", img_green);
//		//imshow("result", img_gray);
//
//		int wait = int(1.0 / fps * 25);
//
//		if (waitKey(1) == 27)
//			break;
//
//	}
//
//
//}
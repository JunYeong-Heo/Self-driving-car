//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//#define RED 2
//#define GREEN 3
//#define YELLOW 4
//
//int main()
//{
//	int range_count = 0;
//
//	Scalar red(0, 0, 255);
//	Scalar blue(255, 0, 0);
//	Scalar yellow(0, 255, 255);
//
//	Scalar magenta(255, 0, 255);
//
//	Mat rgb_color = Mat(1, 1, CV_8UC3, red);
//	Mat hsv_color;
//
//	cvtColor(rgb_color, hsv_color, COLOR_BGR2HSV);
//
//
//	int hue = (int)hsv_color.at<Vec3b>(0, 0)[0];
//	int saturation = (int)hsv_color.at<Vec3b>(0, 0)[1];
//	int value = (int)hsv_color.at<Vec3b>(0, 0)[2];
//
//
//	cout << "hue = " << hue << endl;
//	cout << "saturation = " << saturation << endl;
//	cout << "value = " << value << endl;
//
//
//	int low_hue = hue - 10;
//	int high_hue = hue + 10;
//
//	int low_hue1 = 0, low_hue2 = 0;
//	int high_hue1 = 0, high_hue2 = 0;
//
//	if (low_hue < 10) {
//		range_count = 2;
//
//		high_hue1 = 180;
//		low_hue1 = low_hue + 180;
//		high_hue2 = high_hue;
//		low_hue2 = 0;
//	}
//	else if (high_hue > 170) {
//		range_count = 2;
//
//		high_hue1 = low_hue;
//		low_hue1 = 180;
//		high_hue2 = high_hue - 180;
//		low_hue2 = 0;
//	}
//
//	else {
//		range_count = 1;
//
//		low_hue1 = low_hue;
//		high_hue1 = high_hue;
//	}
//
//	/*cout << low_hue1 << "  " << high_hue1 << endl;
//	cout << low_hue2 << "  " << high_hue2 << endl;*/
//
//
//	VideoCapture cap(0);
//	Mat img_frame, img_hsv;
//
//
//	if (!cap.isOpened()) {
//		cerr << "ERROR! Unable to open camera\n";
//		return -1;
//	}
//
//
//	for (;;)
//	{
//		// wait for a new frame from camera and store it into 'frame'
//		cap.read(img_frame);
//
//		// check if we succeeded
//		if (img_frame.empty()) {
//			cerr << "ERROR! blank frame grabbed\n";
//			break;
//		}
//
//
//		//HSV로 변환
//		cvtColor(img_frame, img_hsv, COLOR_BGR2HSV);
//
//
//		//지정한 HSV 범위를 이용하여 영상을 이진화
//		Mat img_mask1, img_mask2, img_mask3, img_mask4;
//		inRange(img_hsv, Scalar(low_hue1, 50, 50), Scalar(high_hue1, 255, 255), img_mask1);
//		if (range_count == 2) {
//			inRange(img_hsv, Scalar(low_hue2, 50, 50), Scalar(high_hue2, 255, 255), img_mask2);
//			img_mask1 |= img_mask2;
//		}
//
//		inRange(img_hsv, Scalar(70, 80, 100), Scalar(140, 255, 255), img_mask3);
//		inRange(img_hsv, Scalar(30, 80, 100), Scalar(70, 255, 255), img_mask4);
//
//		//if (range_count == 3) {
//		//	inRange(img_hsv, Scalar(low_hue2, 50, 50), Scalar(high_hue2, 255, 255), img_mask3);
//		//}
//
//		//if (range_count == 4) {
//		//	inRange(img_hsv, Scalar(low_hue2, 50, 50), Scalar(high_hue2, 255, 255), img_mask4);
//		//}
//
//		//morphological opening 작은 점들을 제거 
//		erode(img_mask1, img_mask1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_mask1, img_mask1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		erode(img_mask3, img_mask3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_mask3, img_mask3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		erode(img_mask4, img_mask4, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(img_mask4, img_mask4, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		//morphological closing 영역의 구멍 메우기 
//		dilate(img_mask1, img_mask1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_mask1, img_mask1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		dilate(img_mask3, img_mask3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_mask3, img_mask3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		dilate(img_mask4, img_mask4, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(img_mask4, img_mask4, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//
//		//라벨링 
//		Mat img_labels_red, stats_red, centroids_red;
//		Mat img_labels_yellow, stats_yellow, centroids_yellow;
//		Mat img_labels_green, stats_green, centroids_green;
//		int numOfLables_red = connectedComponentsWithStats(img_mask1, img_labels_red, stats_red, centroids_red, 8, CV_32S);
//		int numOfLables_yellow = connectedComponentsWithStats(img_mask4, img_labels_yellow, stats_yellow, centroids_yellow, 8, CV_32S);
//		int numOfLables_green = connectedComponentsWithStats(img_mask3, img_labels_green, stats_green, centroids_green, 8, CV_32S);
//
//		//영역박스 그리기 빨
//		int max_red = -1, idx_red = 0;
//		for (int j = 1; j < numOfLables_red; j++) {
//			int area = stats_red.at<int>(j, CC_STAT_AREA);
//			if (max_red < area)
//			{
//				max_red = area;
//				idx_red = j;
//			}
//		}
//
//
//		int left_red = stats_red.at<int>(idx_red, CC_STAT_LEFT);
//		int top_red = stats_red.at<int>(idx_red, CC_STAT_TOP);
//		int width_red = stats_red.at<int>(idx_red, CC_STAT_WIDTH);
//		int height_red = stats_red.at<int>(idx_red, CC_STAT_HEIGHT);
//
//
//		rectangle(img_frame, Point(left_red, top_red), Point(left_red + width_red, top_red + height_red), Scalar(0, 0, 255), 1);
//		
//		//영역박스 노
//		int max_yellow = -1, idx_yellow = 0;
//		for (int j = 1; j < numOfLables_yellow; j++) {
//			int area = stats_yellow.at<int>(j, CC_STAT_AREA);
//			if (max_yellow < area)
//			{
//				max_yellow = area;
//				idx_yellow = j;
//			}
//		}
//
//
//		int left_yellow = stats_yellow.at<int>(idx_yellow, CC_STAT_LEFT);
//		int top_yellow = stats_yellow.at<int>(idx_yellow, CC_STAT_TOP);
//		int width_yellow = stats_yellow.at<int>(idx_yellow, CC_STAT_WIDTH);
//		int height_yellow = stats_yellow.at<int>(idx_yellow, CC_STAT_HEIGHT);
//
//		rectangle(img_frame, Point(left_yellow, top_yellow), Point(left_yellow + width_yellow, top_yellow + height_yellow), Scalar(0, 255, 255), 1);
//
//		//영역박스 초
//		int max_green = -1, idx_green = 0;
//		for (int j = 1; j < numOfLables_green; j++) {
//			int area = stats_green.at<int>(j, CC_STAT_AREA);
//			if (max_green < area)
//			{
//				max_green = area;
//				idx_green = j;
//			}
//		}
//
//		int left_green = stats_green.at<int>(idx_green, CC_STAT_LEFT);
//		int top_green = stats_green.at<int>(idx_green, CC_STAT_TOP);
//		int width_green = stats_green.at<int>(idx_green, CC_STAT_WIDTH);
//		int height_green = stats_green.at<int>(idx_green, CC_STAT_HEIGHT);
//
//		rectangle(img_frame, Point(left_green, top_green), Point(left_green + width_green, top_green + height_green), Scalar(0, 255, 0), 1);
//
//#define THRESHOLD_PIXEL 12000
//
//		if (countNonZero(img_mask1) > THRESHOLD_PIXEL)
//		{
//			vector<Vec3f> circles;
//			HoughCircles(img_mask1, circles, HOUGH_GRADIENT, 1, 125, 250, 25);
//
//			//putText(img_frame, "RED", Point(100, 300), 1, 3, Scalar(255, 0, 0), 3);
//
//			if (circles.size() >= 1 && circles.size() <= 3)
//			{
//				for (int i = 0; i < circles.size(); i++) {
//					Point center((int)(circles[i][0] + 0.5), (int)(circles[i][1] + 0.5));
//					int radius = (int)(circles[i][2]);
//					circle(img_frame, center, radius, Scalar(255, 0, 0), 3);
//				}
//				putText(img_frame, "STOP", Point(200, 400), 1, 3, Scalar(50, 50, 255), 5);
//			}
//		}
//		
//		imshow("Red", img_mask1);
//		imshow("Green", img_mask3);
//		imshow("Yellow", img_mask4);
//		imshow("Origin", img_frame);
//
//		if (waitKey(1) >= 0)
//			break;
//	}
//
//
//	return 0;
//}
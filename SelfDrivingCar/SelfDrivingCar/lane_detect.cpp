//#include <iostream>
//#include "opencv2/opencv.hpp"
//#include "pch.hpp"
//
//#define MIN_AREA_PIXELS 300
//#define LINE_SPACING_PIXELS 30
//
//using namespace cv;
//using namespace std;
//
//#define NORMAL_STATE 0
//#define STOP_STATE 1
//#define TUNNEL_STATE 2
//#define TRAFFIC_LIGHTS_STATE 3
//
//#define POSITION_Y 151 //will be adjuted
//#define FRAME_WIDTH 320
//
////HSV Color Condition (YELLOW)
//#define Y_H_LOW 20
//#define Y_H_HIGH 70
//#define Y_S_LOW 60
//#define Y_S_HIGH 250
//#define Y_V_LOW 30
//#define Y_V_HIGH 255
////HSV Color Condition (Red)
//#define R_H_LOW 0
//#define R_H_HIGH 60
//#define R_S_LOW 10
//#define R_S_HIGH 255
//#define R_V_LOW 10
//#define R_V_HIGH 255
////HSV Color Condition (Green)
//#define G_H_LOW 60
//#define G_H_HIGH 160
//#define G_S_LOW 0
//#define G_S_HIGH 255
//#define G_V_LOW 0
//#define G_V_HIGH 255
////HSV Color Condition (White)
//#define W_H_LOW 0
//#define W_H_HIGH 360
//#define W_S_LOW 0
//#define W_S_HIGH 45
//#define W_V_LOW 230
//
//#define W_V_HIGH 255
//
//#define VALUE_THRESHOLD 183
//
//#pragma once
//
//class CLine {
//public:
//	Point center;
//	double rate;
//	double y_inter;
//	int left;
//	int width;
//	Point start;
//	Point end;
//	CLine(double rate, Point center, int left, int width) {
//		this->rate = rate;
//		this->left = left;
//		this->center = center;
//		this->width = width;
//		y_inter = -rate * center.x + center.y;
//		double x1 = rate;
//		double y1 = rate * x1 + y_inter;
//		double x2 = left + width;
//		double y2 = rate * x2 + y_inter;
//		start = Point(x1, y1);
//		end = Point(x2, y2);
//	}
//
//	double dist_to_point(Point p) {
//		double x1 = p.x;
//		double y1 = p.y;
//		double a = rate;
//		double b = -1.0;
//		double c = -rate * center.x + center.y;
//		double d = fabs(a * x1 + b * y1 + c) / sqrt(a * a + b * b);
//		return d;
//	}
//};
//class CurrentLane {
//public:
//	Point roi_v, roi_x, roi_y;
//	double angle;
//
//	CurrentLane(double angle, Point roi_v, Point roi_x, Point roid_y) {
//		this->angle = angle;
//		this->roi_v = roi_v;
//		this->roi_x = roi_x;
//		this->roi_y = roi_y;
//	}
//};
//
//class LaneDetect {
//public:
//	Mat preprocessing(Mat frame, Rect roi, Rect roileft, Rect roiright);
//	int extractLine(CLine* lines, int num_labels, Mat src_img, Mat img_labels, Mat stats, Mat centroids);
//	void displayLineinfo(Mat img, CLine* lines, int num_lines, Scalar linecolor, Scalar captioncolor, int width, int height);
//	void detectcolor(Mat& image, double minH, double maxH, double minS, double maxS, Mat& mask);
//	double getAngle(Point a, Point b, Point c);
//	void currentLane(Mat& image, double* angle, Point& curv, Point& curx, Point& cury, CLine* lines_R, CLine* lines_L, int right_lines, int left_lines, int* check);
//
//};
//Mat LaneDetect::preprocessing(Mat frame, Rect roi, Rect roileft, Rect roiright) {
//	/*��ó��*/
//	Mat	grayImage, otsuImage, closedImage, blurImage;
//
//	cvtColor(frame, grayImage, COLOR_BGR2GRAY);	//�׷��̽����Ϸ� ��ȯ
//	adaptiveThreshold(grayImage, otsuImage, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 81, -50);//������threshold
//	Mat morphfillter(4, 4, CV_8U, Scalar(1)); //��������
//	morphologyEx(otsuImage, closedImage, MORPH_CLOSE, morphfillter);	//Ŭ��¡����					
//	medianBlur(closedImage, blurImage, 3);
//
//	return blurImage;
//}
//
//int LaneDetect::extractLine(CLine* lines, int num_labels, Mat src_img, Mat img_labels, Mat stats, Mat centroids)
//{
//	int line_index = 0;
//
//	vector<Vec4i> blob_lines;
//	// Labelled image blob�� ��� üũ (i=0�� ���� ����̹Ƿ� ����)
//	for (int i = 1; i < num_labels; i++)
//	{
//		// blob area�� �ʹ� ������ ����
//		if (stats.at<int>(i, CC_STAT_AREA) < MIN_AREA_PIXELS) continue;
//		// Houghtrasform �� line ���� ����,
//		//line�� �ϳ��� ���� ������ ��� ���ĸ� �����ϰ� ���� blob���� �Ѿ��
//		HoughLinesP(src_img, blob_lines, 1, CV_PI / 180, 100, 100, 2);
//
//		if (blob_lines.size() == 0) continue;
//
//		// Transform �� ����� line ���� �߿� ���� �� line�� ã�´�
//		double longDistance = 0;
//		int longDistanceIndex = 0;
//		for (int j = 0; j < blob_lines.size(); j++)
//		{
//			Vec4i L = blob_lines[j];
//			double distance = (L[2] - L[0]) * (L[2] - L[0]) + (L[3] - L[1]) * (L[3] - L[1]);
//			if (distance > longDistance && distance > LINE_SPACING_PIXELS * 2) {
//				longDistance = distance;
//				longDistanceIndex = j;
//			}
//		}
//
//		// ���� �� line ������ ���⸦ �̿��� �̹��� blob�� center�� �������� ���ο� line ����
//		Vec4i L = blob_lines[longDistanceIndex];
//		double rate = ((double)(L[3] - L[1])) / ((double)(L[2] - L[0]) + 0.5); // �и� 0�� �Ǵ� ���(���Ѵ� ����)�� ���� ���� �и� 0.5�� �����ش�
//		int unique_line_flag = 1;
//
//		// �̹� ������ line�� �ߺ��Ǵ�(�ʹ� �����) line�� ���� �������� �ʴ´� 
//		for (int k = 0; k < line_index; k++) {
//			if (lines[k].dist_to_point(Point(L[0], L[1])) < LINE_SPACING_PIXELS) unique_line_flag = 0;
//		}
//
//		// ���ο� line�� ��� �����Ͽ� lines �޸� ������ ����
//		if (unique_line_flag) {
//			double centerx = centroids.at<double>(i, 0);
//			double centery = centroids.at<double>(i, 1);
//			int left = stats.at<int>(i, CC_STAT_LEFT);
//			int width = stats.at<int>(i, CC_STAT_WIDTH);
//			lines[line_index] = CLine(rate, Point((int)centerx, (int)centery), left, width);
//			line_index++;
//		}
//	}
//	// ������ line ������ ��ȯ
//	return line_index;
//}
//void LaneDetect::displayLineinfo(Mat img, CLine* lines, int num_lines, Scalar linecolor, Scalar captioncolor, int width, int height) {
//	for (int i = 0; i < num_lines; i++) {
//		double x1, x2, y1, y2;
//
//		/*img�� ��ü frame�̱� ������ width, height�� ������
//		roiframe�̶�� ������ �ʿ� ����*/
//		x1 = lines[i].left;
//		x2 = lines[i].left + lines[i].width;
//		y1 = lines[i].rate * x1 + lines[i].y_inter;
//		y2 = lines[i].rate * x2 + lines[i].y_inter;
//		line(img, Point((int)x1 + width, (int)y1 + height), Point((int)x2 + width, (int)y2 + height), linecolor, 1, LINE_AA);
//
//
//		char text[15];
//		double tanval = -atan2(lines[i].rate, 1.0) / (double)CV_PI;
//
//		if (tanval < 0)
//			tanval = tanval + 1.0;
//		sprintf_s(text, "%.2lfpi", tanval);
//		putText(img, text, lines[i].center, 2, 0.5, captioncolor);
//
//	}
//}
//void LaneDetect::detectcolor(Mat& image, double minH, double maxH, double minS, double maxS, Mat& mask) {
//	Mat hsv;
//	vector<Mat> channels;
//	cvtColor(image, hsv, COLOR_BGR2HSV);
//	split(hsv, channels);
//	Mat mask1;
//	threshold(channels[0], mask1, maxH, 255, THRESH_BINARY_INV);
//	Mat mask2;
//	threshold(channels[0], mask2, minH, 255, THRESH_BINARY);
//	Mat hmask;
//	if (minH < maxH)
//		hmask = mask1 & mask2;
//	else
//		hmask = mask1 | mask2;
//
//	threshold(channels[1], mask1, maxS, 255, THRESH_BINARY_INV);
//	threshold(channels[1], mask2, minS, 255, THRESH_BINARY);
//
//	Mat smask;
//	smask = mask1 & mask2;
//	mask = hmask & smask;
//
//}
//double LaneDetect::getAngle(Point a, Point b, Point c) {
//	Point ab = { b.x - a.x,b.y - a.y };
//	Point cb = { b.x - c.x,b.y - c.y };
//
//	double inner = (ab.x * cb.x + ab.y * cb.y);
//	double l1 = sqrt(ab.x * ab.x + ab.y * ab.y);
//	double l2 = sqrt(cb.x * cb.x + cb.y * cb.y);
//
//	double lx1 = ab.x / l1;
//	double ly1 = ab.y / l1;
//	double lx2 = cb.x / l2;
//	double ly2 = cb.y / l2;
//
//	inner = (lx1 * lx2 + ly1 * ly2);
//	double result = acos(inner) * 180 / CV_PI;
//
//	return result;
//}
//void LaneDetect::currentLane(Mat& image, double* angle, Point& curv, Point& curx, Point& cury, CLine* lines_R, CLine* lines_L, int right_lines, int left_lines, int* check) {
//	double al, bl, ar, br;
//	int x, y;
//	int num_lines = left_lines;
//	double x1L, x2L, y1L, y2L, x1R, x2R, y1R, y2R;
//	vector<double> angles;
//	vector<Point> X;
//	vector<Point> Y;
//	vector<Point> V;
//	vector<Point> ROI_Vertices;
//
//	int index = 0;
//
//
//	Mat mask = Mat(image.rows, image.cols, CV_8UC1);
//
//	for (int k = 0; k < image.cols; k++)
//		for (int m = 0; m < image.rows; m++)
//			mask.at<uchar>(Point(k, m)) = 0;
//
//	Mat imageDest = Mat(image.rows, image.cols, CV_8UC3);
//	vector<Point> ROI_Poly;
//	Point v;
//	if (left_lines > right_lines) {
//		num_lines = right_lines;
//
//	}
//	V.resize(num_lines);
//	X.resize(num_lines);
//	Y.resize(num_lines);
//	angles.resize(num_lines);
//	for (int i = 0; i < num_lines; i++) {
//
//		x1L = lines_L[i].left;
//		x2L = lines_L[i].left + lines_L[i].width;
//		y1L = lines_L[i].rate * x1L + lines_L[i].y_inter;
//		y2L = lines_L[i].rate * x2L + lines_L[i].y_inter;
//		x1R = lines_R[i].left;
//		x2R = lines_R[i].left + lines_R[i].width;
//		y1R = lines_R[i].rate * x1R + lines_R[i].y_inter;
//		y2R = lines_R[i].rate * x2R + lines_R[i].y_inter;
//
//		x1R += (image.cols / 2);
//		x2R += (image.cols / 2);
//
//		al = (y2L - y1L) / (x2L - x1L);
//		bl = y1L - (y2L - y1L) / (x2L - x1L) * x1L;
//		ar = (y2R - y1R) / (x2R - x1R);
//		br = y1R - (y2R - y1R) / (x2R - x1R) * x1R;
//
//		x = (int)(-(bl - br) / (al - ar));
//		y = (int)(al * (-(bl - br) / (al - ar)) + bl);
//
//		if ((x >= 0 && x <= mask.cols) && (y >= 0 && y <= mask.rows))
//		{
//
//			V[i] = Point(x, y);
//
//			X[i] = Point(lines_L[i].start.x, lines_L[i].start.y);
//			Y[i] = Point(lines_R[i].end.x + image.cols / 2, lines_R[i].end.y);
//
//			//���� ����,�����ʿ����ȿ� ������ ����
//			if ((X[i].x >= 0 && X[i].x <= image.cols / 2) && (Y[i].x > image.cols / 2 && Y[i].x <= image.cols))
//			{
//
//				if (X[i].y > Y[i].y) {
//					double y_inter = lines_L[i].y_inter;
//					double rate = lines_L[i].rate;
//					X[i].y = Y[i].y;
//					X[i].x = (X[i].y - y_inter) / rate;    //y = rate * x + y_inter;y_inter = -rate*center.x + center.y;
//				}
//				else {
//					double rate = lines_R[i].rate;
//					double y_inter = lines_R[i].y_inter;
//					double d = Y[i].y - X[i].y;
//					Y[i].y = X[i].y;
//					Y[i].x = Y[i].y * (1 / rate) + image.cols / 2;
//
//				}
//				angles[i] = getAngle(X[i], V[i], Y[i]);
//
//				if (*angle > angles[i])
//				{
//					*angle = angles[i];
//					index = i;
//
//					curv = V[index];
//					curx = X[index];
//					cury = Y[index];
//
//					(*check)++;
//				}
//
//				ROI_Vertices.push_back(curv);
//				ROI_Vertices.push_back(curx);
//				ROI_Vertices.push_back(cury);
//
//				approxPolyDP(ROI_Vertices, ROI_Poly, 1.0, true);
//				fillConvexPoly(mask, &ROI_Poly[0], ROI_Poly.size(), 255, 8, 0);
//
//
//				image.copyTo(imageDest, mask);
//			}
//
//		}
//
//	}
//
//
//}
//int main()
//{
//	cout << "***** Lane Detectection Program *** by. JY * JH * CH *****" << endl;
//	cout << "File name: ";
//	char filename[50];
//	cin >> filename;
//	VideoCapture capture(filename);
//	LaneDetect lanedetect;
//	if (!capture.isOpened())
//	{
//		cout << "Can not open capture !!!" << endl;
//		return 0;
//	}
//
//	/*�������� ũ��*/
//	int width, height;
//	width = (int)capture.get(CAP_PROP_FRAME_WIDTH);
//	height = (int)capture.get(CAP_PROP_FRAME_HEIGHT);
//	Size size = Size((int)width, (int)height);
//
//	cout << "size: " << size << endl;
//
//	/*�������� fps(�ʴ� �����Ӽ�)*/
//	int fps = (int)(capture.get(CAP_PROP_FPS));
//
//	cout << "fps: " << fps << endl;
//
//	int frameNum = -1;
//	Mat frame, roiframe, roiframe_L, roiframe_R;
//	int roi_x = 0, roi_y = height / 3; //���ɿ��� �������� ��ǥ x,y
//									   //width = 1280;
//									   //height = 720/2=340;
//									   /*������ 1/3�������� �Ʒ� 1/2�� ������ ROI�� ����*/
//
//	/*���ɿ��� ����*/
//	//Parameter: ��������(x,y), ���ɿ����� ũ��
//	Rect roi(roi_x, roi_y, width, height / 2);
//	Rect roileft(roi_x, roi_y, width / 2, height / 2);
//	Rect roiright((width - roi_x) / 2, roi_y, width / 2, height / 2);
//
//	CurrentLane* curlane;
//	double smallA = 150;
//	Point crx;
//	Point cry;
//	Point crv;
//	int check = 0;
//
//	while (char(waitKey(1)) != 'q' && capture.isOpened())
//	{
//		capture >> frame;
//		if (frame.empty())
//			break;
//		cout << "Detect CurrentLane..." << endl;
//
//		/*���ɿ��� ����*/
//		roiframe = frame(roi);
//		roiframe_L = frame(roileft);
//		roiframe_R = frame(roiright);
//
//		Mat preImage, edgeImage;
//		/*��ó��*/
//		preImage = lanedetect.preprocessing(frame, roi, roileft, roiright);
//		Canny(preImage, edgeImage, 100, 210, 3);
//
//		/*�����̹��� ��������*/
//		Mat roiEdge_R, roiEdge_L;
//		roiEdge_R = edgeImage(roiright);
//		roiEdge_L = edgeImage(roileft);
//
//		/*�¿쿵���� �󺧸�*/
//		//�󺧸��� �ʿ��� ����
//		Mat img_labels_R, stats_R, centroids_R;
//		Mat img_labels_L, stats_L, centroids_L;
//
//		/*�¿� Labelled ������ ����*/
//		int numOfLabels_R = connectedComponentsWithStats(roiEdge_R, img_labels_R, stats_R, centroids_R, 8, CV_32S);
//		int numOfLabels_L = connectedComponentsWithStats(roiEdge_L, img_labels_L, stats_L, centroids_L, 8, CV_32S);
//
//		// Labelled �������� ������ ������ �����ϱ� ���� �޸� �Ҵ� (�ִ� label ������ŭ)		
//		CLine* lines_R = (CLine*)malloc(sizeof(CLine) * numOfLabels_R);
//		CLine* lines_L = (CLine*)malloc(sizeof(CLine) * numOfLabels_L);
//
//		/*Labelled �������� ���� ����*/
//		int right_lines = lanedetect.extractLine(lines_R, numOfLabels_R, roiEdge_R, img_labels_R, stats_R, centroids_R);
//		int left_lines = lanedetect.extractLine(lines_L, numOfLabels_L, roiEdge_L, img_labels_L, stats_L, centroids_L);
//
//		lanedetect.currentLane(roiframe, &smallA, crv, crx, cry, lines_R, lines_L, right_lines, left_lines, &check);
//
//		//�����Ҵ� �޸� ����
//		free(lines_R);
//		free(lines_L);
//		cout << check << endl;
//		/*���� ���� ǥ��*/
//		if (check >= 0) {
//			vector<Point> Lane;
//			vector<Point> fillLane;
//
//			Lane.push_back(crv);
//			Lane.push_back(crx);
//			Lane.push_back(cry);
//
//			Mat temp(roiframe.rows, roiframe.cols, CV_8UC1);
//			for (int i = 0; i < temp.cols; i++)
//				for (int j = 0; j < temp.rows; j++)
//					temp.at<uchar>(Point(i, j)) = 0;
//
//			Mat curlane(roiframe.rows, roiframe.cols, CV_8UC3);
//			Mat curarea(roiframe.rows, roiframe.cols, CV_8UC3);
//			line(temp, crx, crv, 255, 3);
//			line(temp, cry, crv, 255, 3);
//			approxPolyDP(Lane, fillLane, 1.0, true);
//
//
//			fillConvexPoly(temp, &fillLane[0], fillLane.size(), 255, 8, 0);
//
//
//			fillConvexPoly(curlane, &fillLane[0], fillLane.size(), Scalar(255, 255, 0), 8, 0);
//
//			addWeighted(roiframe, 0.7, curlane, 0.2, 0.0, roiframe);
//		}
//
//		/*���� â*/
//		namedWindow("frame", 0);
//		imshow("frame", frame);
//		imshow("temp", roiframe);
//
//	}
//	return 0;
//}
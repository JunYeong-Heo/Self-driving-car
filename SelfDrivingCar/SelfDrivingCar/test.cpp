//#include <iostream>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//
//using namespace std;
//using namespace cv;
//
//#define NORMAL_STATE 0
//#define STOP_STATE 1
//#define TUNNEL_STATE 2
//#define TRAFFIC_LIGHTS_STATE 3
//
//#define POSITION_Y 151 //will be adjuted
//#define FRAME_WIDTH 320
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
//void setroi(Mat& InputImg, Mat& OutputImg, Point&& pt1, Point&& pt2)
//{
//	Rect roiRect = Rect(pt1, pt2);
//	Mat roi(InputImg, roiRect);
//	OutputImg = roi;
//}
//
//int main_fffffff(void)
//{
//	VideoCapture cap("output1.mp4");
//	int state = NORMAL_STATE;
//
//	cap.set(CAP_PROP_FRAME_WIDTH, 320);
//	cap.set(CAP_PROP_FRAME_HEIGHT, 240);
//
//	if (!cap.isOpened())
//	{
//		cout << "비디오 오픈 실패" << endl;
//		return -1;
//	}
//
//	Mat img_original;
//
//	while (1)
//	{
//		cap.read(img_original);
//		flip(img_original, img_original, 1);
//		Mat img_edge;
//		Canny(img_original, img_edge, 200, 250);
//		imshow("Canny", img_edge);
//
//		//선 감지를 위한 허프변환
//		vector<Vec2f> lines;
//		HoughLines(img_edge, lines, 1, CV_PI / 180, 80);
//
//		Mat result(img_edge.rows, img_edge.cols, CV_8U, Scalar(255));
//
//		vector<Vec2f>::const_iterator it = lines.begin();
//
//		while (it != lines.end())
//		{
//			float rho = (*it)[0];		//첫번째 요소는 rho 거리
//			float theta = (*it)[1];		//두번째 요소는 delta 각도
//
//			if (theta < CV_PI / 4. || theta > 3. * CV_PI)//수직 행
//			{
//				Point pt1(rho / cos(theta), 0);		//첫행에서 해당 선의 교차점
//				Point pt2((rho - result.rows * sin(theta)) / cos(theta), result.rows);
//				//마지막 행에서 해당선의 교차점
//				line(img_original, pt1, pt2, Scalar(255, 0, 0), 2);
//				cout.setf(ios::fixed); cout.precision(3);
//
//				if (cos(2 * theta) >= 0.95)
//					cout << "상태 : 직진 \t (cos2*theta) : " << cos(2 * theta) << endl;
//				else if (cos(2 * theta) < 0.95 && theta < 0.375)
//					cout << "상태 : 우회전 \t (cos2*theta) : " << cos(2 * theta) << endl;
//				else if (cos(2 * theta) < 0.95 && theta > 0.375)
//					cout << "상태 : 좌회전 \t (cos2*theta) : " << cos(2 * theta) << endl;
//			}
//			else
//			{
//				Point pt1(0, rho / sin(theta));
//				Point pt2(result.cols, (rho - result.cols * cos(theta)) / sin(theta));
//
//				line(img_original, pt1, pt2, Scalar(0, 0, 255), 2);
//			}
//			++it;
//		}
//
//		imshow("Lane detect", img_original);
//
//		if (waitKey(1) == 27)
//			break;
//
//		
//		switch (state)
//		{
//		case NORMAL_STATE:
//			break;
//		case STOP_STATE:
//			cout << "stop state" << endl;
//			break;
//		case TUNNEL_STATE:
//			cout << "tunnel state" << endl;
//			break;
//		case TRAFFIC_LIGHTS_STATE:
//			cout << "traffic zone" << endl;
//			break;
//		default:
//			break;
//		}
//
//	}
//}
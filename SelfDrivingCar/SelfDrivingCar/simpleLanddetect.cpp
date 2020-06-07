//#include <opencv2/core.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main(void)
//{
//	Mat frame;
//	VideoCapture cap("Lane.mp4");
//
//	int fps = cap.get(CAP_PROP_FPS);
//
//	Mat img_original, img_edge;
//
//	if (!cap.isOpened())
//	{
//		cerr << "open err" << endl;
//		return -1;
//	}
//
//	while (1)
//	{
//		cap.read(img_original);
//
//		if (img_original.empty())
//		{
//			cerr << "cap err" << endl;
//			return -1;
//		}
//		//�׷��� ������ �������� ��ȯ ����
//		cvtColor(img_original, img_edge, COLOR_BGR2GRAY);
//		//ĳ�Ͽ����� �̿��Ͽ� ���� ������ �����մϴ�.  
//		Canny(img_edge, img_edge, 100, 200, 3);
//
//		Mat img_right(img_edge, Rect(img_edge.cols / 2, img_edge.rows / 2, img_edge.cols / 2, img_edge.rows / 2));
//		Mat img_left(img_edge, Rect(0, 0, img_edge.cols / 2, img_edge.rows / 2));
//
//		imshow("asd", img_right);
//		imshow("asdgh", img_left);
//
//		//���� ������ �����մϴ�.  
//		vector<Vec2f> lines_right;
//		HoughLines(img_right, lines_right, 1, CV_PI / 180, 40);
//
//		vector<Vec2f> lines_left;
//		HoughLines(img_left, lines_left, 1, CV_PI / 180, 40);
//
//
//		////������ ������ ���� �׷��ݴϴ�.  
//		//for (int i = 0; i < lines_right.size(); i++)
//		//{
//
//		//}
//
//
//		int wait = int(1.0 / fps * 25);
//		if (waitKey(wait) >= 0)
//			break;
//	}
//}
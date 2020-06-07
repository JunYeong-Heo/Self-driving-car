#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(void)
{
    VideoCapture cap("14.mp4");

    cap.set(CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CAP_PROP_FRAME_HEIGHT, 240);

    if (!cap.isOpened())
    {
        cout << "���� ���� ����" << endl;
        return -1;
    }

    for (;;)
    {
        Mat frame;
        cap.read(frame);
        //flip(frame, frame, 1);
        //imshow("frame", frame);

        Mat contours;
        Canny(frame, contours, 200, 250);
        imshow("Canny", contours);

        //�� ������ ���� ������ȯ
        vector<Vec2f> lines;
        HoughLines(contours, lines, 1, CV_PI / 180, 80);

        Mat result(contours.rows, contours.cols, CV_8U, Scalar(255));

        vector<Vec2f>::const_iterator it = lines.begin();
        vector<Vec2f> mean;

        while (it != lines.end())
        {
            float rho = (*it)[0];      //ù��° ��Ҵ� rho �Ÿ�
            float theta = (*it)[1];      //�ι�° ��Ҵ� delta ����
            if (theta < CV_PI / 4. || theta > 3. * CV_PI)//���� ��
            {
                Point pt1(rho / cos(theta), 0);      //ù�࿡�� �ش� ���� ������
                Point pt2((rho - result.rows * sin(theta)) / cos(theta), result.rows);
                //������ �࿡�� �ش缱�� ������
                line(frame, pt1, pt2, Scalar(255, 0, 0), 2);
                cout.setf(ios::fixed);
                cout.precision(3);

                if (cos(2 * theta) >= 0.95)
                    cout << "���� \t theta : " << theta << endl;
                else if (cos(2 * theta) < 0.95 && theta < 1)
                    cout << "��ȸ�� \t theta : " << theta << endl;
                else if (cos(2 * theta) < 0.95 && theta > 1)
                    cout << "��ȸ�� \t theta : " << theta << endl;
            }
            else
            {
                Point pt1(0, rho / sin(theta));
                Point pt2(result.cols, (rho - result.cols * cos(theta)) / sin(theta));

                line(frame, pt1, pt2, Scalar(0, 0, 255), 2);
            }
            ++it;
        }

        imshow("Original", frame);

        if (waitKey(20) == 27)
            break;
    }
}
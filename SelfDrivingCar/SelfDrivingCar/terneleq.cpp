////#include <opencv2/opencv.hpp>
////
////using namespace cv;
////using namespace std;
////
////void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256)
////{
////    int        histSize[] = { bins };            // 히스토그램 계급개수
////    float   range[] = { 0, (float)range_max };        // 히스토그램 범위
////    int        channels[] = { 0 };                // 채널 목록
////    const float* ranges[] = { range };
////
////    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
////}
////
////void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 200))
////{
////    hist_img = Mat(size, CV_8U, Scalar(255));
////    float  bin = (float)hist_img.cols / hist.rows;
////    normalize(hist, hist, 0, size.height, NORM_MINMAX);
////
////    for (int i = 0; i < hist.rows; i++)
////    {
////        float idx1 = i * bin;
////        float idx2 = (i + 1) * bin;
////        Point2f pt1 = Point2f(idx1, 0);
////        Point2f pt2 = Point2f(idx2, hist.at <float>(i));
////
////        if (pt2.y > 0)
////            rectangle(hist_img, pt1, pt2, Scalar(0), -1);
////    }
////    flip(hist_img, hist_img, 0);
////}
////
////void create_hist(Mat img, Mat& hist, Mat& hist_img)
////{
////    int histzise = 256, range = 256;
////    calc_Histo(img, hist, histzise, range);
////    draw_histo(hist, hist_img);
////}
////
////int main()
////{
////    Mat image = imread("darkload.png", 0); //영상 읽기
////    CV_Assert(image.data);
////    imshow("src_User", image);
////
////    //cvtColor(image, image, COLOR_BGR2YCrCb);
////    
////    Mat hist, dst1, dst2, hist_img, hist_img1, hist_img2;
////    create_hist(image, hist, hist_img); //히스토그램 및 그래프 그리기
////
////    //히스토그램 누적합 계산
////    Mat accum_hist = Mat(hist.size(), hist.type(), Scalar(0));
////    accum_hist.at<float>(0) = hist.at<float>(0);
////
////    for (int i = 1; i < hist.rows; i++) {
////        accum_hist.at<float>(i) = accum_hist.at<float>(i - 1) + hist.at<float>(i);
////    }
////
////    accum_hist /= sum(hist)[0];
////    accum_hist *= 255;
////    dst1 = Mat(image.size(), CV_8U);
////
////    for (int i = 0; i < image.rows; i++) {
////        for (int j = 0; j < image.cols; j++) {
////            int idx = image.at<uchar>(i, j);
////            dst1.at<uchar>(i, j) = (uchar)accum_hist.at<float>(idx);
////        }
////    }
////
////    equalizeHist(image, dst2);
////    create_hist(dst1, hist, hist_img1);
////    create_hist(dst2, hist, hist_img2);
////
////    imshow("User_hist", hist_img1), imshow("dst1_User", dst1);
////    imshow("Equalize_hist", hist_img2);
////
////    waitKey();
////    return 0;
////}
////
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//// 멤버 변수 정의
//class Histogram1D {
//private:
//    int histSize[1]; // 빈도수
//    float hranges[2]; // 최소/최대 화소값
//    const float* ranges[1];
//    int channels[1]; // 여기서 1채널만 사용
//public:
//    Histogram1D() { // 1차원 히스토그램을 위한 인자 준비
//        histSize[0] = 256;
//        hranges[0] = 0.0;
//        hranges[1] = 255.0;
//        ranges[0] = hranges;
//        channels[0] = 0; // 기본적으로 채널을 0으로 보기
//    }
//
//    // 정의한 멤버 변수로 그레이레벨 영상의 히스토그램을 계산할 때는 다음 메소드를 사용해 수행
//    cv::MatND getHistogram(const cv::Mat& image) {
//        // 1차원(1D) 히스토그램 계산.
//        cv::MatND hist;
//        cv::calcHist(&image, // 히스토그램 계산 
//            1,   // 단일 영상의 히스토그램만
//            channels, // 대상 채널               
//            cv::Mat(), // 마스크 사용하지 않음     
//            hist,  // 결과 히스토그램         
//            1,   // 1차원(1D) 히스토그램           
//            histSize, // 빈도수                  
//            ranges  // 화소값 범위             
//            );
//        return hist;
//    }
//
//    // 값의 순서만으로 의미를 파악하기 어려우므로 바 그래프를 사용
//    // 그래프를 생성하는 메소드
//    cv::Mat getHistogramImage(const cv::Mat& image) {
//        // 1차원(1D) 히스토그램을 계산하고, 영상으로 반환
//
//        cv::MatND hist = getHistogram(image); // 먼저 히스토그램 계산
//
//        double maxVal = 0; // 최대 빈도수 가져오기
//        double minVal = 0; // 최소 빈도수 가져오기
//        cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
//
//        cv::Mat histImg(histSize[0], histSize[0], CV_8U, cv::Scalar(255));
//        // 히스토그램을 출력하기 위한 영상
//
//        int hpt = static_cast<int>(0.9 * histSize[0]);
//        // nbins의 90%를 최대점으로 설정
//
//
//        for (int h = 0; h < histSize[0]; h++) { // 각 빈도에 대한 수직선을 그리기 
//            float binVal = hist.at<float>(h);
//            int intensity = static_cast<int>(binVal * hpt / maxVal);
//            cv::line(histImg, cv::Point(h, histSize[0]), cv::Point(h, histSize[0] - intensity), cv::Scalar::all(0));
//            // 두 점 간의 거리를 그리는 함수
//        }
//        return histImg;
//    }
//};
//
//int main()
//{
//    cv::Mat image = cv::imread("darkload.png", 0);
//
//    if (!image.data)
//        return 0;
//
//    cv::namedWindow("Image");
//    cv::imshow("Image", image);
//
//   
//    Histogram1D h;
//    cv::MatND histo = h.getHistogram(image);
//
//    for (int i = 0; i < 256; i++) // 각 빈도 조회
//        std::cout << "Value " << i << " = " << histo.at<float>(i) << std::endl;
//
//    cv::imshow("src histogram", h.getHistogramImage(image));
//
//    cv::waitKey(0);
//
//    equalizeHist(image, image);
//
//    histo = h.getHistogram(image);
//    for (int i = 0; i < 256; i++) // 각 빈도 조회
//        std::cout << "Value " << i << " = " << histo.at<float>(i) << std::endl;
//
//    cv::imshow("dst histogram", h.getHistogramImage(image));
//
//    cv::imshow("dst image", image);
//
//    cv::waitKey(0);
//
//    return 0;
//}
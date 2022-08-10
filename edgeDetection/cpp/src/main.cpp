#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	string path = "E:/cmake/edgeDetection/images/01.bmp";
	Mat src = cv::imread(path, cv::IMREAD_COLOR);

	if (src.empty())
	{
		cout << "Can not load image." << endl;
		return -1;
	}

	cv::imshow("src", src);
	cv::waitKey();

	// 灰度化
	Mat gray;
	cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	cv::imshow("gray", gray);
	cv::waitKey();

	// 边缘提取
	Mat edge;
	cv::Canny(gray, edge, 50, 100, 3, true);
	cv::imshow("edge", edge);
	cv::waitKey();

	// 闭运算
	Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, Size(3, 3));
	Mat close;
	cv::morphologyEx(edge, close, cv::MORPH_CLOSE, kernel);
	cv::imshow("close", close);
	cv::waitKey();

	// 提取轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	cv::findContours(close, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	// 绘制轮廓
	Mat dst(src.size(), CV_8UC3, Scalar(0, 0, 0));

	// 绘制所有轮廓
	//drawContours(dst, contours, -1, Scalar(0, 255, 0), 1);

	for (int i = 0; i < contours.size(); i++)
	{
		
		
		// 用面积过滤轮廓
		double area = cv::contourArea(contours[i]);

		if (area > 100.0)
		{
			// 获取最小外接矩形
			cv::RotatedRect rect = cv::minAreaRect(contours[i]);
			int cx, cy;
			cx = int(rect.center.x);
			cy = int(rect.center.y);
			float width, height;
			width = rect.size.width;
			height = rect.size.height;

			// 判断是否是矩形
			if (std::max(width, height) / std::min(width, height) < 1.5)
			{
				// 画示意线


			}



			// 绘制单个轮廓
			cv::drawContours(dst, contours, i, Scalar(0, 255, 0), 1, 8, hierarchy);
			cv::imshow("dst", dst);
			cv::waitKey();
		}


	}


	return 0;
}
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

	// �ҶȻ�
	Mat gray;
	cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	cv::imshow("gray", gray);
	cv::waitKey();

	// ��Ե��ȡ
	Mat edge;
	cv::Canny(gray, edge, 50, 100, 3, true);
	cv::imshow("edge", edge);
	cv::waitKey();

	// ������
	Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, Size(3, 3));
	Mat close;
	cv::morphologyEx(edge, close, cv::MORPH_CLOSE, kernel);
	cv::imshow("close", close);
	cv::waitKey();

	// ��ȡ����
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	cv::findContours(close, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	// ��������
	Mat dst(src.size(), CV_8UC3, Scalar(0, 0, 0));

	// ������������
	//drawContours(dst, contours, -1, Scalar(0, 255, 0), 1);

	for (int i = 0; i < contours.size(); i++)
	{
		
		
		// �������������
		double area = cv::contourArea(contours[i]);

		if (area > 100.0)
		{
			// ��ȡ��С��Ӿ���
			cv::RotatedRect rect = cv::minAreaRect(contours[i]);
			int cx, cy;
			cx = int(rect.center.x);
			cy = int(rect.center.y);
			float width, height;
			width = rect.size.width;
			height = rect.size.height;

			// �ж��Ƿ��Ǿ���
			if (std::max(width, height) / std::min(width, height) < 1.5)
			{
				// ��ʾ����


			}



			// ���Ƶ�������
			cv::drawContours(dst, contours, i, Scalar(0, 255, 0), 1, 8, hierarchy);
			cv::imshow("dst", dst);
			cv::waitKey();
		}


	}


	return 0;
}
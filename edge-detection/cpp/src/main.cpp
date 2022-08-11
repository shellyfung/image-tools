#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	string path = "E:/opensource/image-tools/edge-detection/images/01.jpg";
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
		
		// ���Ƶ�������
		//cv::drawContours(dst, contours, i, Scalar(0, 255, 0), 1, 8, hierarchy);
		//cv::imshow("dst", dst);
		//cv::waitKey();

		// �������������
		double area = cv::contourArea(contours[i]);

		if (area > 200.0)
		{
				
			// ��ȡ��С��Ӿ���
			cv::RotatedRect rect = cv::minAreaRect(contours[i]);

			// ������С������
			cv::Point2f vertices[4];
			rect.points(vertices);
			for (int j = 0; j < 4; j++)
			{
				cv::line(dst, vertices[j], vertices[(j + 1) % 4], Scalar(0, 255, 0));
			}

			float width, height;
			width = rect.size.width;
			height = rect.size.height;

			// �ж��Ƿ��Ǿ���
			if (std::max(width, height) / std::min(width, height) < 1.5)
			{
				// ��ʾ����
				cv::Point start, end;
				start.x = int((vertices[0].x + vertices[1].x) * 0.5);
				start.y = int((vertices[0].y + vertices[1].y) * 0.5);
				end.x = int((vertices[2].x + vertices[3].x) * 0.5);
				end.y = int((vertices[2].y + vertices[3].y) * 0.5);
				cv::line(dst, start, end, Scalar(0, 0, 255));
				// �������
				Point center;
				center.x = int(rect.center.x);
				center.y = int(rect.center.y);
				cv::putText(dst, std::to_string(width), center, cv::FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0));
			}

			cv::imshow("dst", dst);
			cv::waitKey();

		}

	}


	return 0;
}
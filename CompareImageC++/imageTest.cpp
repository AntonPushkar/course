#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int averageColor(Mat &img, int width, int height);

int main()
{

	Mat img = imread("C:\\Users\\Anton\\Desktop\\C++\\VSCourse\\CompareImageC++\\test1.png");
	Mat out_img;

	int width = 16;
	int heigth = 16;
	
	resize(img, out_img, CvSize(16, 16));

	cvtColor(out_img, out_img, CV_BGR2GRAY);

	imwrite("C:\\Users\\Anton\\Desktop\\C++\\VSCourse\\CompareImageC++\\test2.png", out_img);

	cout << averageColor(out_img, width, heigth)<<" average " << endl;
	
	return 0;
}

int averageColor(Mat &img, int width, int height)
{
	int average = 0;
	int resolution = width * height;
	
	int sumColor = 0;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			sumColor += (int) img.at<uchar>(Point(i, j));
		}
	}

	average = sumColor / resolution;

	return average;

}
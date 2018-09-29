#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int averageColor(Mat &img, int resolution);
void chainBits(Mat &img, int *bits, int average);
void processImages(Mat &firstImg, Mat &secImg, int heigth, int width);
void saveImages(Mat &firstImg, Mat &secImg);
int hammingDist(int *bits1img, int* bits2img, int resolution);



int main()
{
	string pathOne;
	string pathTwo;
	cout << "Input two pathes to image" << endl;
	cin >> pathOne;
	cin >> pathTwo;

	Mat firstImg = imread(pathOne);
	Mat secondImg = imread(pathTwo);

	const int width = 16;
	const int heigth = 16;
	const int resolution = width * heigth;

	processImages(firstImg, secondImg, heigth, width);
	saveImages(firstImg, secondImg);

	int averageFirst = averageColor(firstImg, resolution);
	cout << averageFirst <<" average color of first image " << endl;
	int averageSecond = averageColor(secondImg, resolution);
	cout << averageSecond << " average color of second image " << endl;


	
	int bits1Image[resolution];
	int bits2Image[resolution];

	chainBits(firstImg, bits1Image, averageFirst);
	chainBits(secondImg, bits2Image, averageSecond);

	int hammDist = hammingDist(bits1Image, bits2Image, resolution);

	cout << "Distance of Hamming = " << hammDist << endl;

	if (hammDist < 10 && hammDist>5)
	{
		cout << "Images is similar" << endl;
	}
	else if (hammDist >= 0 && hammDist < 5)
	{
		cout << "Images if the same" << endl;
	}
	else if (hammDist > 10)
	{
		cout << "Images is different" << endl;
	}


	return 0;
}

void processImages(Mat &firstImg, Mat &secImg, int heigth, int width)
{
	resize(firstImg, firstImg, CvSize(heigth, width));
	cvtColor(firstImg, firstImg, CV_BGR2GRAY);
	
	resize(secImg, secImg, CvSize(heigth, width));

	cvtColor(secImg, secImg, CV_BGR2GRAY);

	
}

void saveImages(Mat &firstImg, Mat &secImg)
{
	imwrite("C:\\Users\\Anton\\Desktop\\C++\\VSCourse\\CompareImageC++\\FirstImg.png", firstImg);
	imwrite("C:\\Users\\Anton\\Desktop\\C++\\VSCourse\\CompareImageC++\\SecImg.png", secImg);
}
int averageColor(Mat &img, int resolution)
{
	int average = 0;

	
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


void chainBits(Mat &img, int *bits, int average )
{
	
	for (int i = 0, rl = 0; i < img.rows; i++)
	{
		
		for (int j = 0; j < img.cols; j++, rl++)
		{
			
			if ((int)img.at<uchar>(Point(i, j)) > average)
			{
				bits[rl] = 1;
			}
			else
			{
				bits[rl] = 0;
			
			}
		}
	}
}

int hammingDist(int *bits1img, int* bits2img, int resolution)
{
	int hammingDist = 0;
	
	for (int i = 0; i < resolution; i++)
	{
		if (bits1img[i] != bits2img[i])
		{
			hammingDist++;
		}
	}

	return hammingDist;
}
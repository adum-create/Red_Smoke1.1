#ifndef SMOKERECOGNIZE_H
#define SMOKERECOGNIZE_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include"RedAnalyze.h"

using namespace cv;
using namespace std;

class SmokeRecongnize
{
public:
	SmokeRecongnize();
	~SmokeRecongnize();

	//�������
	static Mat subImg(Mat img_before, Mat img_after, double threshold);

	//С������
	static void filter(Mat &src, int rows, int cols, int threshold);

	//����������������ֵ
	static vector<int> setCoordinate(Mat src);
	
	//��������ֵ��ȡ��������
	static Mat regionExtraction(Mat src, int xRoi, int yRoi, int widthRoi, int heightRoi);

	//����ʶ�����ɫ����
	static double recognizeAnalyze(Mat first_img, Mat second_img, double threshold1, int threshold2, double a);

	//�ж�����ͼ���Ƿ�һ��
	static bool matIsEqual(const cv::Mat mat1, const cv::Mat mat2);

	//ˮ�غ�ɫ����
	static double poolAnalyze(Mat first_img);



};

#endif //SMOKERECOGNIZE_H
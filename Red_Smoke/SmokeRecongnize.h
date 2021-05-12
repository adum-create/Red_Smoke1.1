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

	//背景差分
	static Mat subImg(Mat img_before, Mat img_after, double threshold);

	//小窗过滤
	static void filter(Mat &src, int rows, int cols, int threshold);

	//计算烟雾区域坐标值
	static vector<int> setCoordinate(Mat src);
	
	//根据坐标值提取烟雾区域
	static Mat regionExtraction(Mat src, int xRoi, int yRoi, int widthRoi, int heightRoi);

	//烟雾识别和颜色分析
	static double recognizeAnalyze(Mat first_img, Mat second_img, double threshold1, int threshold2, double a);

	//判断两个图像是否一致
	static bool matIsEqual(const cv::Mat mat1, const cv::Mat mat2);

	//水池红色计算
	static double poolAnalyze(Mat first_img);



};

#endif //SMOKERECOGNIZE_H
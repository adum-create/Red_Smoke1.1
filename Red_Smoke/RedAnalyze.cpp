#include "RedAnalyze.h"



RedAnalyze::RedAnalyze()
{
}


RedAnalyze::~RedAnalyze()
{
}

/*RGB分析红色相对值方法*/
double RedAnalyze::redAnalyze2(Mat roiImg, double threshold)
{
	//图片参数获取
	roiImg.convertTo(roiImg, CV_32FC3);
	int rows = roiImg.rows;
	int cols = roiImg.cols;

	//红色数值
	double red_value = 0;

	//如果图形小于参数就直接置为0
	if ((rows <= threshold) || (cols <= threshold))
	{
		return red_value;
	}

	//如果不是就继续处理
	for (int i = 0; i  < i < (rows - threshold); i = i+ threshold)
	{
		for (int j = 0; j < (cols - threshold); j = j+ threshold)
		{
			//计算每个小的矩阵值
			double sum_B = 0;
			double sum_G = 0;
			double sum_R = 0;
			double this_red = 0;

			for (int rr = 0; rr < threshold; rr++)
			{
				for (int cc = 0; cc < threshold; cc++)
				{
					sum_R = sum_R + roiImg.at<Vec3f>(i+rr, j+cc)[2];
					sum_B = sum_B + roiImg.at<Vec3f>(i + rr, j+cc)[0];
					sum_G = sum_G + roiImg.at<Vec3f>(i + rr, j+cc)[1];
				}
			}
			//更新最大红色区域值
			this_red = sum_R * 300 / (sum_R + sum_B + sum_G);
			if (this_red > red_value)
			{
				red_value = this_red;
			}
		}
	}

	

	return red_value;
}

#include "RedAnalyze.h"



RedAnalyze::RedAnalyze()
{
}


RedAnalyze::~RedAnalyze()
{
}

/*RGB������ɫ���ֵ����*/
double RedAnalyze::redAnalyze2(Mat roiImg, double threshold)
{
	roiImg.convertTo(roiImg, CV_32FC3);
	int rows = roiImg.rows;
	int cols = roiImg.cols;
	double sum_B = 0;
	double sum_G = 0;
	double sum_R = 0;
	//�����ɫŨ��
	double sum = 0;
	//���߳�
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			sum_R = sum_R + roiImg.at<Vec3f>(i, j)[2];
			sum_B = sum_B + roiImg.at<Vec3f>(i, j)[0];
			sum_G = sum_G + roiImg.at<Vec3f>(i, j)[1];
		}
	}
	//�ж��Ƿ�Ϊ��ɫ(�������࣬�Ҷ����̴�ܶ�)
	if ((sum_R*1.2>sum_B) && (sum_B*1.2>sum_R) && (2 * sum_G<sum_B) && (2 * sum_G<sum_R))
	{
		if (sum_R>sum_B)
		{
			sum = sum_R * 200 / (sum_R + sum_B) + threshold;
		}
		else
		{
			sum = sum_B * 200 / (sum_R + sum_B) + threshold;
		}

	}
	else
	{
		//����R�ı�ֵ
		sum = sum_R * 300 / (sum_R + sum_B + sum_G);
	}


	return sum;
}

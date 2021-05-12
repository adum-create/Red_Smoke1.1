#include "SmokeRecongnize.h"



SmokeRecongnize::SmokeRecongnize()
{
}


SmokeRecongnize::~SmokeRecongnize()
{
}

/*���*/
Mat SmokeRecongnize::subImg(Mat img_before, Mat img_after, double threshold)
{
	//��ŻҶ�ͼ
	Mat rst_gray(1080, 1920, CV_32FC1);
	Mat img_before_gray(1080, 1920, CV_64FC1);
	Mat img_after_gray(1080, 1920, CV_64FC1);
	Mat rst_gray_sub(1080, 1920, CV_32FC1);
	//��RGB��ɫ�ռ�ת��Ϊ�Ҷȿռ�
	cvtColor(img_before, img_before_gray, COLOR_RGB2GRAY);
	cvtColor(img_after, img_after_gray, COLOR_RGB2GRAY);
	img_before_gray.convertTo(img_before_gray, CV_64FC1);
	img_after_gray.convertTo(img_after_gray, CV_64FC1);
	//    cv::imwrite("img_before_gray.bmp", img_before_gray);
	//    cv::imwrite("img_after_gray.bmp", img_after_gray);

	for (int rows = 0; rows < 1080; rows++)
	{
		for (int cols = 0; cols < 1920; cols++)
		{

			if (abs(img_before_gray.at<double>(rows, cols) - img_after_gray.at<double>(rows, cols)) > threshold)
			{
				rst_gray.at<float>(rows, cols) = 200;
			}
			else
			{
				rst_gray.at<float>(rows, cols) = 0;
			}
			//�����ֵ�������
			//rst_gray_sub.at<float>(rows, cols) = abs(img_before_gray.at<char>(rows, cols) - img_after_gray.at<char>(rows, cols));

		}
	}

	return rst_gray;
}

/*С������*/
void SmokeRecongnize::filter(Mat &src, int rows, int cols, int threshold)
{
	for (int i = 0; i < 1080; i = i + rows)
	{
		for (int j = 0; j < 1920; j = j + cols)

		{

			//���˵�Ԫ����
			int sum = 0;//����0������ʼ��
			for (int rr = 0; rr < rows; rr++)
			{

				for (int cc = 0; cc < cols; cc++)
				{

					if (src.at<float>(i + rr, j + cc) > 0)
					{
						sum += 1;
					}

				}

			}
			//�������0����û�д�����Ϊ0
			if (sum < (rows*cols - threshold))
			{
				for (int rr = 0; rr < rows; rr++)
				{

					for (int cc = 0; cc < cols; cc++)
					{
						src.at<float>(i + rr, j + cc) = 0;
					}
				}
			}

		}
	}
}

/*������������ֵ�����ص����ĸ����ͣ�*/
vector<int> SmokeRecongnize::setCoordinate(Mat src)
{
	int cols = src.cols;
	int rows = src.rows;
	int xmin = 10000, ymin = 10000, xmax = 0, ymax = 0;
	vector<int> rst(4);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (src.at<float>(i, j) > 0)
			{
				//����x��Сֵ
				if (j < xmin)
				{
					xmin = j;
				}
				//����y��Сֵ
				if (i < ymin)
				{
					ymin = i;
				}
				//����x���ֵ
				if (j > xmax)
				{
					xmax = j;
				}
				//����y���ֵ
				if (i > ymax)
				{
					ymax = i;
				}
			}
		}
	}
	rst[0] = xmin;
	rst[1] = xmax;
	rst[2] = ymin;
	rst[3] = ymax;
	return rst;
}

/*��������ֵ��ȡ��������*/
Mat SmokeRecongnize::regionExtraction(Mat src, int xRoi, int yRoi, int widthRoi, int heightRoi)
{
	Mat roiImg(heightRoi, widthRoi, CV_8UC3);
	src(cv::Rect(xRoi, yRoi, widthRoi, heightRoi)).copyTo(roiImg);
	return roiImg;
}

/*����ʶ�����ɫ����*/
double SmokeRecongnize::recognizeAnalyze(Mat first_img, Mat second_img, double threshold1, int threshold2, double a)
{
	double red_test1;    //��ɫ���ֵ

	//�ȼ������ͼƬ�Ƿ�һ�����ж����ֵ
	bool isequal = matIsEqual(first_img, second_img);
	if (isequal == true)
	{
		red_test1 = 0;
	}

	else
	{
		//��������
		vector<int> coordinate_test1(4);
		//������
		Mat sub_test1(1080, 1920, CV_64FC1);
		sub_test1 = subImg(first_img, second_img, threshold1);
		//����
		filter(sub_test1, 9, 16, threshold2);
		//��û�м�⵽��Ե�仯ʱ���Զ�Ϊ0
		int num = 0;
		for (int i = 0; i < 1080; i++)
		{
			for (int j = 0; j < 1920; j++)

			{

				if (sub_test1.at<float>(i, j)>0)
				{
					num++;
				}
				else
				{

				}
			}
		}
		if (num>2)//num����������������С
		{
			//��ȡ����ϵ
			coordinate_test1 = setCoordinate(sub_test1);
			//��ȡ��������
			Mat roiImg_test1((coordinate_test1[3] - coordinate_test1[2]), (coordinate_test1[1] - coordinate_test1[0]), CV_8UC3);
			roiImg_test1 = regionExtraction(first_img, coordinate_test1[0], coordinate_test1[2], (coordinate_test1[1] - coordinate_test1[0]), (coordinate_test1[3] - coordinate_test1[2]));
			//��ɫ���ֵ����
			red_test1 = RedAnalyze::redAnalyze2(roiImg_test1, a);
		}
		else
		{
			red_test1 = 0;
		}


	}

	return red_test1;
}

/*�ж�����ͼ���Ƿ�һ��*/
bool SmokeRecongnize::matIsEqual(const cv::Mat mat1, const cv::Mat mat2)
{
	if (mat1.empty() && mat2.empty()) {
		return true;
	}
	if (mat1.cols != mat2.cols || mat1.rows != mat2.rows || mat1.dims != mat2.dims ||
		mat1.channels() != mat2.channels()) {
		return false;
	}
	if (mat1.size() != mat2.size() || mat1.channels() != mat2.channels() || mat1.type() != mat2.type()) {
		return false;
	}
	int nrOfElements1 = mat1.total()*mat1.elemSize();
	if (nrOfElements1 != mat2.total()*mat2.elemSize()) return false;
	bool lvRet = memcmp(mat1.data, mat2.data, nrOfElements1) == 0;
	return lvRet;
}

/*ˮ�ؼ���*/
double SmokeRecongnize::poolAnalyze(Mat first_img)
{
	    first_img.convertTo(first_img, CV_32FC3);
		int rows = first_img.rows;
		int cols = first_img.cols;
		double sum_B = 0;
		double sum_G = 0;
		double sum_R = 0;

		//�����ɫŨ��
		double sum = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				sum_R = sum_R + first_img.at<Vec3f>(i, j)[2];
				sum_B = sum_B + first_img.at<Vec3f>(i, j)[0];
				sum_G = sum_G + first_img.at<Vec3f>(i, j)[1];

			}
		}

		//����R�ı�ֵ
		sum = sum_R * 300 / (sum_R + sum_B + sum_G);

		return sum;

}




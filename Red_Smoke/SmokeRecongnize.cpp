#include "SmokeRecongnize.h"



SmokeRecongnize::SmokeRecongnize()
{
}


SmokeRecongnize::~SmokeRecongnize()
{
}

/*差分*/
Mat SmokeRecongnize::subImg(Mat img_before, Mat img_after, double threshold)
{
	//存放灰度图
	Mat rst_gray(1080, 1920, CV_32FC1);
	Mat img_before_gray(1080, 1920, CV_64FC1);
	Mat img_after_gray(1080, 1920, CV_64FC1);
	Mat rst_gray_sub(1080, 1920, CV_32FC1);
	//将RGB颜色空间转化为灰度空间
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
			//计算差值后的数组
			//rst_gray_sub.at<float>(rows, cols) = abs(img_before_gray.at<char>(rows, cols) - img_after_gray.at<char>(rows, cols));

		}
	}

	return rst_gray;
}

/*小窗过滤*/
void SmokeRecongnize::filter(Mat &src, int rows, int cols, int threshold)
{
	for (int i = 0; i < 1080; i = i + rows)
	{
		for (int j = 0; j < 1920; j = j + cols)

		{

			//过滤单元矩阵
			int sum = 0;//大于0计数初始化
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
			//如果大于0个数没有达标就置为0
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

/*烟雾区域坐标值（返回的是四个整型）*/
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
				//更新x最小值
				if (j < xmin)
				{
					xmin = j;
				}
				//更新y最小值
				if (i < ymin)
				{
					ymin = i;
				}
				//更新x最大值
				if (j > xmax)
				{
					xmax = j;
				}
				//更新y最大值
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

/*根据坐标值提取烟雾区域*/
Mat SmokeRecongnize::regionExtraction(Mat src, int xRoi, int yRoi, int widthRoi, int heightRoi)
{
	Mat roiImg(heightRoi, widthRoi, CV_8UC3);
	src(cv::Rect(xRoi, yRoi, widthRoi, heightRoi)).copyTo(roiImg);
	return roiImg;
}

/*烟雾识别和颜色分析*/
double SmokeRecongnize::recognizeAnalyze(Mat first_img, Mat second_img, double threshold1, int threshold2, double a)
{
	double red_test1;    //红色相对值

	//先检测两张图片是否一致再判断相对值
	bool isequal = matIsEqual(first_img, second_img);
	if (isequal == true)
	{
		red_test1 = 0;
	}

	else
	{
		//定义坐标
		vector<int> coordinate_test1(4);
		//计算差分
		Mat sub_test1(1080, 1920, CV_64FC1);
		sub_test1 = subImg(first_img, second_img, threshold1);
		//过滤
		filter(sub_test1, 9, 16, threshold2);
		//当没有检测到边缘变化时就自动为0
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
		if (num>2)//num代表检测出来的区域大小
		{
			//获取坐标系
			coordinate_test1 = setCoordinate(sub_test1);
			//提取烟雾区域
			Mat roiImg_test1((coordinate_test1[3] - coordinate_test1[2]), (coordinate_test1[1] - coordinate_test1[0]), CV_8UC3);
			roiImg_test1 = regionExtraction(first_img, coordinate_test1[0], coordinate_test1[2], (coordinate_test1[1] - coordinate_test1[0]), (coordinate_test1[3] - coordinate_test1[2]));
			//红色相对值计算
			red_test1 = RedAnalyze::redAnalyze2(roiImg_test1, a);
		}
		else
		{
			red_test1 = 0;
		}


	}

	return red_test1;
}

/*判断两个图像是否一致*/
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

/*水池计算*/
double SmokeRecongnize::poolAnalyze(Mat first_img)
{
	    first_img.convertTo(first_img, CV_32FC3);
		int rows = first_img.rows;
		int cols = first_img.cols;
		double sum_B = 0;
		double sum_G = 0;
		double sum_R = 0;

		//定义红色浓度
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

		//计算R的比值
		sum = sum_R * 300 / (sum_R + sum_B + sum_G);

		return sum;

}




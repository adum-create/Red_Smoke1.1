#ifndef REDANALYZE_H
#define REDANALYZE_H
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <vector>
#include<cmath>
#include "omp.h"

using namespace cv;
using namespace std;

class RedAnalyze
{
public:
	RedAnalyze();
	~RedAnalyze();

	//RGB·¨·ÖÎö
	static double redAnalyze2(Mat roiImg, double threshold);

};

#endif // REDANALYZE_H



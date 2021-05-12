#ifndef MAT2QIMAGE_H
#define MAT2QIMAGE_H

#include <QImage>
#include <opencv2/core/core.hpp>

QImage Mat2QImage(const cv::Mat& inputMat);

#endif // MAT2QIMAGE_H


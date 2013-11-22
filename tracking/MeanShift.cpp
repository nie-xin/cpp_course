#include "MeanShift.h"

MeanShift::MeanShift() {

}

MeanShift::~MeanShift() {

}

void MeanShift::getHistogramAndBackProjection(cv::Mat img, cv::Rect ROI) {
    int h_bin_size = 50;
    float h_range[] = {0, 256};
    const float * ranges[] = {h_range};
    cv::Mat imgROI_HSV;
    cv::Mat imgROI = img(ROI);

    cvtColor(imgROI, imgROI_HSV, CV_BGR2HSV);
}

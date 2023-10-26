#ifndef YOLOV5_H
#define YOLOV5_H

#include <opencv2/core/core.hpp>
#include <net.h>
#include "cpu.h"

#if defined(USE_NCNN_SIMPLEOCV)
#include "simpleocv.h"
#else
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif
#include <float.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#define YOLOV5_V62 1
#define MAX_STRIDE 64

using namespace cv;
using namespace std;

struct Object
{
    cv::Rect_<float> rect;
    int label;
    float prob;
};

struct GridAndStride
{
    int grid0;
    int grid1;
    int stride;
};

class YoloV5
{
public:
    YoloV5();
    int load(int target_size, float prob_threshold = 0.4f, float nms_threshold = 0.5f);
    int detect(const cv::Mat& rgb, std::vector<Object>& objects);
    int draw(cv::Mat& rgb, const std::vector<Object>& objects);
private:
    ncnn::Net yolo;
    int target_size;
    float prob_threshold;
    float nms_threshold;
    float norm_vals[3];
};

#endif // YOLOV5_H
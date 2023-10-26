#include "yoloV5.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>

YoloV5 yolov5;
int target_size = 320; //640 //416; //320;  must be divisible by 32.


int main(int argc, char** argv)
{
    float fps;
    VideoCapture videoCapture;
    Mat videoFrame;
    yolov5.load(target_size);

    // open camera
    videoCapture.open(0);
    videoCapture.set(CAP_PROP_FRAME_WIDTH, 640);
    videoCapture.set(CAP_PROP_FRAME_HEIGHT, 480);
    namedWindow("VideoCapture", WINDOW_AUTOSIZE);

    if(!videoCapture.isOpened())
    {
        std::cout<<"Failed to open camera."<<std::endl;
        return (-1);
    }
     else
    {
        std::cout << "Hit ESC to exit" << "\n" ;
        while (true)
        {
            videoCapture.read(videoFrame);
            
            std::vector<Object> objects;
            double timer = (double)cv::getTickCount();
            yolov5.detect(videoFrame, objects);
            fps = cv::getTickFrequency() / ((double)cv::getTickCount() - timer);
            cv::putText(videoFrame,std::to_string(fps),cv::Point(50, 400),cv::FONT_HERSHEY_SIMPLEX,1,{ 255, 255, 255 },2);
            yolov5.draw(videoFrame, objects);

            imshow("VideoCapture", videoFrame);
            int keycode = cv::waitKey(10) & 0xff ; 
            if (keycode == 27) break ;
        }
    }
    videoCapture.release();
    cv::destroyAllWindows() ;

    return 0;
}

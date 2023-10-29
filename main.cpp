#include "yoloV5.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>

// Serial library
#include "serialib.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define SERIAL_PORT "/dev/ttyACM0"

YoloV5 yolov5;
int target_size = 320; //640 //416; //320;  must be divisible by 32.

volatile sig_atomic_t flag = 0;
pthread_mutex_t mutex_result = PTHREAD_MUTEX_INITIALIZER;

int objs_type = 4;

void sigint_handler(int signum) {
    flag = 1; // Đặt biến flag để thoát khỏi vòng lặp
}

void* fn_serial(void *args){
    // Serial object
    serialib serial;
    // Connection to serial port
    char errorOpening = serial.openDevice(SERIAL_PORT, 115200);
    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening != 1) {
        printf("Error opening serial port: %d\n", errorOpening);
        return (void*)errorOpening;
    }
    printf ("Successful connection to %s\n",SERIAL_PORT);
    char buffer[15];

    while (!flag) {
        pthread_mutex_lock(&mutex_result);
        int type = objs_type;
        pthread_mutex_unlock(&mutex_result);

        snprintf(buffer, sizeof(buffer), "%d", objs_type);
        serial.writeString(buffer);
        // printf("String sent: %s\n", buffer);
        sleep(1);
    }
    printf ("Close serial!\n");
    serial.closeDevice();
    return NULL;
}

int main(int argc, char** argv) 
{
    pthread_t thread_serial = 0;
    pthread_create(&thread_serial, NULL, &fn_serial, NULL);
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
    }else{
        std::cout << "Hit ESC or Ctrl+C to exit" << "\n";
        signal(SIGINT, sigint_handler); // Đặt sự kiện Ctrl+C
        while (true) {
            videoCapture.read(videoFrame);

            std::vector<Object> objects;
            double timer = (double)cv::getTickCount();
            yolov5.detect(videoFrame, objects);
            fps = cv::getTickFrequency() / ((double)cv::getTickCount() - timer);
            if (!objects.empty()) {
                for (const Object& obj : objects) {
                    // printf("label: %d\n", obj.label);
                    pthread_mutex_lock(&mutex_result);
                    objs_type = obj.label;
                    pthread_mutex_unlock(&mutex_result);
                }
            } else {
                pthread_mutex_lock(&mutex_result);
                objs_type = 4;
                pthread_mutex_unlock(&mutex_result);
            }

            cv::putText(videoFrame, std::to_string(fps), cv::Point(50, 400), cv::FONT_HERSHEY_SIMPLEX, 1, {255, 255, 255}, 2);
            yolov5.draw(videoFrame, objects);

            imshow("VideoCapture", videoFrame);
            int keycode = cv::waitKey(10) & 0xff;
            if (keycode == 27) break;
        }
    }
    pthread_join(thread_serial, NULL);
    videoCapture.release();
    cv::destroyAllWindows();
    
    return 0;
}

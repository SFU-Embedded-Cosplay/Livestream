#pragma once

#include <iostream>

#include <opencv2/opencv.hpp>

class Camera {
public:
    Camera();
    ~Camera();

    cv::Mat getFrame();

private:
    cv::VideoCapture cap;
};

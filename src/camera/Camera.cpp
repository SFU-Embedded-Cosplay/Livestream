#include "Camera.h"


Camera::Camera() {
    cap.open(0);
    if(!cap.isOpened()) {
        std::cout << "camera failed" << std::endl;
        exit(-1);
    }
}

cv::Mat Camera::getFrame() {
    cv::Mat frame;
    cap >> frame;

    return frame;
}

Camera::~Camera() {

}

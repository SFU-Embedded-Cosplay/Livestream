#include "Camera.h"


Camera::Camera() {
    using namespace cv;

    VideoCapture cap(0);
    if(!cap.isOpened()) {
        std::cout << "camera failed" << std::endl;
        return;
    }

    Mat edges;
    namedWindow("edges", 1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        //cvtColor(frame, edges, CV_BGR2GRAY);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        std::cout << frame.size[0] << " - " << frame.size[1] << std::endl;
        imshow("edges", frame); //edges
        if(waitKey(30) >= 0) break;
    }
}

Camera::~Camera() {

}

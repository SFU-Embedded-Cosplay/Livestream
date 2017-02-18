#pragma once

#include <iostream>
#include <cstring>
#include <string>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <linux/videodev2.h>
#include <libv4l2.h>

typedef struct {
    size_t length;
    void* data; // you must manually free the allocated data array
} Frame_t;

class Camera {
public:
    Camera();
    ~Camera();

    Frame_t getFrame();

    static const std::string VIDEO_DEVICE_DRIVER_PATH;
    static const size_t FRAME_WIDTH;
    static const size_t FRAME_HEIGHT;
private:

    void setFormat(struct v4l2_format &format);
    static int xioctl(int fileDescriptor, int request, void *arguments);

    int cameraFileDescriptor;

    //cv::VideoCapture cap;
};

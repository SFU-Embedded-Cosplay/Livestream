#include "Camera.h"

const std::string Camera::VIDEO_DEVICE_DRIVER_PATH = "/dev/video0";
const size_t Camera::FRAME_WIDTH = 1920;
const size_t Camera::FRAME_HEIGHT = 1080;


Camera::Camera() {
    struct v4l2_format format;

    cameraFileDescriptor = v4l2_open(VIDEO_DEVICE_DRIVER_PATH.c_str(), O_RDWR | O_NONBLOCK, 0);
    if (cameraFileDescriptor < 0) {
            std::cerr << "FATAL ERROR: Cannot open USB video camera at: " << VIDEO_DEVICE_DRIVER_PATH << std::endl;
            exit(EXIT_FAILURE);
    }

    setFormat(format);
}

void Camera::setFormat(struct v4l2_format &format) {
    assert(cameraFileDescriptor != 0);

    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = FRAME_WIDTH;
    format.fmt.pix.height = FRAME_HEIGHT;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_H264; // V4L2_PIX_FMT_RGB24; // set pixel capture mode to MPEG-4 AVC mode
    format.fmt.pix.field = V4L2_FIELD_INTERLACED;

    xioctl(cameraFileDescriptor, VIDIOC_S_FMT, &format);
    if (format.fmt.pix.pixelformat != V4L2_PIX_FMT_H264) {
            std::cerr << "FATAL ERROR: Camera did not change to H264 format. This webcam may not support H264 encoding.\n";
            exit(EXIT_FAILURE);
    }
}

int Camera::xioctl(int fileDescriptor, int request, void *arguments)
{
        int response;

        do {
            response = ioctl(fileDescriptor, request, arguments);
        } while (-1 == response && EINTR == errno);

        return response;
}

Frame_t Camera::getFrame() {
    struct v4l2_requestbuffers requestBuffer;
    struct v4l2_buffer buffer;
    enum v4l2_buf_type bufferType;
    Frame_t frame;


    // request that a buffer be queued
    requestBuffer.count = 1;
    requestBuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    requestBuffer.memory = V4L2_MEMORY_MMAP;

    xioctl(cameraFileDescriptor, VIDIOC_REQBUFS, &requestBuffer);

    // get a pointer to the video data buffer on the camera
    memset(&buffer, 0, sizeof(buffer));
    buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buffer.memory = V4L2_MEMORY_MMAP;
    buffer.index = 0;

    xioctl(cameraFileDescriptor, VIDIOC_QUERYBUF, &buffer);

    // memory map buffer to frame
    frame.length = buffer.length;
    frame.data = v4l2_mmap(
        NULL,
        buffer.length,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        cameraFileDescriptor,
        buffer.m.offset
    );

    if (MAP_FAILED == frame.data) {
        std::cerr << "FATAL ERROR: mmap() failure occured when trying to load a frame from the webcamera.\n";
        exit(EXIT_FAILURE);
    }


    // enque a buffer
    memset(&buffer, 0, sizeof(buffer));
    buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buffer.memory = V4L2_MEMORY_MMAP;
    buffer.index = 0;
    xioctl(cameraFileDescriptor, VIDIOC_QBUF, &buffer);



    // start capturing image data
    bufferType = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    xioctl(cameraFileDescriptor, VIDIOC_STREAMON, &bufferType);

    fd_set fileDescriptors;
    struct timeval timeout;

    int response = 0;
    do {
        FD_ZERO(&fileDescriptors);
        FD_SET(cameraFileDescriptor, &fileDescriptors);

        /* Timeout. */
        timeout.tv_sec = 10;
        timeout.tv_usec = 10;

        response = select(cameraFileDescriptor + 1, &fileDescriptors, NULL, NULL, &timeout);
    } while ((response == -1 && (errno = EINTR)));

    if (response == -1) {
        std::cerr << "select\n";
        //return nullptr;
    }

    // deque the buffer
    // memset(&buffer, 0, sizeof(buffer));
    buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buffer.memory = V4L2_MEMORY_MMAP;
    xioctl(cameraFileDescriptor, VIDIOC_DQBUF, &buffer);

    // could process the buffer at this point with a callback in the future.

    // enque the buffer again
    xioctl(cameraFileDescriptor, VIDIOC_QBUF, &buffer);

    // stop streaming
    bufferType = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    xioctl(cameraFileDescriptor, VIDIOC_STREAMOFF, &bufferType);

    return frame;
}

Camera::~Camera() {
    close(cameraFileDescriptor);
}

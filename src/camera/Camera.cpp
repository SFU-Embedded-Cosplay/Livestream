#include "Camera.h"

const std::string Camera::VIDEO_DEVICE_DRIVER_PATH = "/dev/video0";
const size_t Camera::FRAME_WIDTH = 1920;
const size_t Camera::FRAME_HEIGHT = 1080;


Camera::Camera(size_t numberOfBuffers) :
        numberOfBuffers(numberOfBuffers),
        frames(NULL) {
    struct v4l2_format format;

    cameraFileDescriptor = v4l2_open(VIDEO_DEVICE_DRIVER_PATH.c_str(), O_RDWR | O_NONBLOCK, 0);
    if (cameraFileDescriptor < 0) {
            std::cerr << "FATAL ERROR: Cannot open USB video camera at: " << VIDEO_DEVICE_DRIVER_PATH << std::endl;
            exit(EXIT_FAILURE);
    }

    setFormat(format);
    mapInMemoryBuffersToCameraBuffers(numberOfBuffers);
    enqueuBuffers(numberOfBuffers);
    startStreaming();
}

Camera::~Camera() {
    for (int i = 0; i < numberOfBuffers; ++i) {
        v4l2_munmap(frames[i].data, frames[i].length);
    }
    delete[] frames;
    v4l2_close(cameraFileDescriptor);
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

void Camera::mapInMemoryBuffersToCameraBuffers(size_t numberOfBuffers) {
    struct v4l2_requestbuffers requestBuffer;
    struct v4l2_buffer buffer;

    // request that a buffer be queued
    requestBuffer.count = numberOfBuffers;
    requestBuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    requestBuffer.memory = V4L2_MEMORY_MMAP;

    if (xioctl(cameraFileDescriptor, VIDIOC_REQBUFS, &requestBuffer) == -1) {
        std::cout << "ERROR: could not query camera buffer with size: " << numberOfBuffers << " because: " << strerror(errno) << "\n";
    }


    assert(frames == NULL);
    frames = new Frame_t[numberOfBuffers];

    for(int i = 0; i < requestBuffer.count; ++i) {
        // get a pointer to the video data buffer on the camera
        memset(&buffer, 0, sizeof(buffer));
        buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buffer.memory = V4L2_MEMORY_MMAP;
        buffer.index = i;

        if (xioctl(cameraFileDescriptor, VIDIOC_QUERYBUF, &buffer) == -1) {
            std::cerr << "ERROR: could not map buffer to memory because: " << strerror(errno) << "\n";
        }

        // memory map buffer to frame
        frames[i].length = buffer.length;
        frames[i].data = v4l2_mmap(
            NULL,
            buffer.length,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            cameraFileDescriptor,
            buffer.m.offset
        );

        if (MAP_FAILED == frames[i].data) {
            std::cerr << "FATAL ERROR: mmap() failure occured when trying to map a buffer to the webcameras memory.\n";
            exit(EXIT_FAILURE);
        }
    }
}

void Camera::enqueuBuffers(size_t numberOfBuffers) {
    struct v4l2_buffer buffer;

    // enque all buffer
    for (int i = 0; i < numberOfBuffers; ++i) {
        memset(&buffer, 0, sizeof(buffer));

        buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buffer.memory = V4L2_MEMORY_MMAP;
        buffer.index = i;

        if (xioctl(cameraFileDescriptor, VIDIOC_QBUF, &buffer) == -1) {
            std::cerr << "FATAL ERROR: Could not enqueu a buffer because: " << strerror(errno) << "\n";
            exit(EXIT_FAILURE);
        }
    }
}

void Camera::startStreaming() {
    // start capturing image data
    enum v4l2_buf_type bufferType = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (xioctl(cameraFileDescriptor, VIDIOC_STREAMON, &bufferType) == -1) {
        std::cerr << "FATAL ERROR: Could not start streaming because: " << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
}

void Camera::stopStreaming() {
    enum v4l2_buf_type bufferType = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (xioctl(cameraFileDescriptor, VIDIOC_STREAMOFF, &bufferType) == -1) {
        std::cerr << "FATAL ERROR: Could not start streaming because: " << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
}

Frame_t Camera::getFrame() {
    struct v4l2_buffer buffer;

    fd_set fileDescriptors;
    struct timeval timeout;

    for (int i = 0; i < numberOfBuffers; i++) {
        int response = 0;
        do {
            FD_ZERO(&fileDescriptors);
            FD_SET(cameraFileDescriptor, &fileDescriptors);

            /* Timeout. */
            timeout.tv_sec = 0;
            timeout.tv_usec = 41667; //1,000,000 / 24 = 41666.6666...;

            response = select(cameraFileDescriptor + 1, &fileDescriptors, NULL, NULL, &timeout);
        } while ((response == -1 && (errno = EINTR)));

        if (response == -1) {
            std::cerr << "select\n";
            continue;
            // return NULL;
        }

        if (response == 0) {
            // select timed out
            std::cout << "could not get frame\n";
            continue;
        }

        // deque the buffer
        memset(&buffer, 0, sizeof(buffer));
        buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buffer.memory = V4L2_MEMORY_MMAP;
        xioctl(cameraFileDescriptor, VIDIOC_DQBUF, &buffer);

        // could process the buffer at this point with a callback in the future.
        std::cout << "used 1: " << buffer.bytesused << "\n";
        frames[buffer.index].dataLength = buffer.bytesused;

        // re queue the buffer again
        xioctl(cameraFileDescriptor, VIDIOC_QBUF, &buffer);

        std::cout << "used 2: " << buffer.bytesused << "\n";

        return frames[buffer.index];
    }

    Frame_t frame = {
        .length = 0,
        .dataLength = 0,
        .data = NULL
    };

    return frame;
}

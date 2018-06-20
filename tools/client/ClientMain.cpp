#include <iostream>
#include <string>

#include "RTMPStream.h"
#include "Camera.h"

#include <bitset>

void writeFrame(std::string out_name, Frame_t frame) {
    FILE* fout = fopen(out_name.c_str(), "a");

    fwrite(frame.data, frame.dataLength, 1, fout);
    fclose(fout);
}

int main() {
    // rtmp://live-ord.twitch.tv/app/live_<values>_<values>
    RTMPStream stream("rtmp://live-sea.twitch.tv/app/live_<values>_<values>", 30 * 1000);
    stream.startStream();

    Camera cam(1);

    int framesPerSecond = 30;
    int durationInSeconds = 10 * 1;
    int frameRate = framesPerSecond * durationInSeconds;

    std::string rawFileName = "recording.raw";
    std::string mp4FileName = "recording.mp4";

    // If you don't remove the old raw video this then the new video will be appended to the old video.
    remove(rawFileName.c_str());

    for(int i = 0; i < frameRate; i++) {
        Frame_t frame = cam.getFrame();

        stream.sendData((char*) frame.data, frame.dataLength);
        writeFrame(rawFileName, frame);
    }

    cam.stopStreaming();

    // add the header onto the raw mp4 data.
    std::string mp4HeaderCommand = "ffmpeg -f h264 -i " + rawFileName + " -vcodec copy " + mp4FileName;
    system(mp4HeaderCommand.c_str());

    return 0;
}

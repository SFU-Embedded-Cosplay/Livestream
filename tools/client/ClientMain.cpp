#include <iostream>
#include <string>

#include "RTPPacket.h"
#include "UDPClient.h"
#include "UDPServer.h"
#include "Camera.h"

#include <bitset>

void writeFrame(std::string out_name, Frame_t frame) {
    FILE* fout = fopen(out_name.c_str(), "w");

    fwrite(frame.data, frame.length, 1, fout);
    fclose(fout);
}

int main() {
    std::cout << "starting\n";

    Camera cam(1);
    int frameRate = 24;

    struct timeval t1, t2;
    double elapsedTime;

    // start timer
    gettimeofday(&t1, NULL);

    for(int i = 0; i < frameRate; i++) {
        Frame_t frame = cam.getFrame();
        std::cout << frame.length << " done\n";
        writeFrame("1.raw", frame);
    }

    cam.stopStreaming();

    // stop timer
    gettimeofday(&t2, NULL);

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    std::cout << elapsedTime << " ms.\n";

    /*
    Frame_t frame = cam.getFrame(); writeFrame("0.ppm", frame);
    std::cout << frame.length << "\n";
    frame = cam.getFrame(); writeFrame("1.ppm", frame);
    frame = cam.getFrame(); writeFrame("2.ppm", frame);
    frame = cam.getFrame(); writeFrame("3.ppm", frame);
    frame = cam.getFrame(); writeFrame("4.ppm", frame);
    frame = cam.getFrame(); writeFrame("5.ppm", frame);
    frame = cam.getFrame(); writeFrame("6.ppm", frame);
    frame = cam.getFrame(); writeFrame("7.ppm", frame);
    frame = cam.getFrame(); writeFrame("8.ppm", frame);
    frame = cam.getFrame(); writeFrame("9.ppm", frame);
    frame = cam.getFrame(); writeFrame("10.ppm", frame);
    /*





    std::cout << frame.length << std::endl;
    /*
    RTPPacket packet(260, 0, 1024, "hello world");
    std::string msg = packet.getNetworkMessage();

    std::cout << msg << ": "<< msg.size() << std::endl;

    packet.printBinaryInformation();

    // std::cout << cam.getFrame().size() << std::endl;

    UDPClient udp("127.0.0.1", 8080);
    UDPServer server(8081);

    udp.send("hello world");
    std::cout << "client received: '" + server.receive() + "'" << std::endl;
*/
    return 0;
}

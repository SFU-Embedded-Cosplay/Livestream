# install cmake for building the project
sudo apt-get install cmake

# install v4l2 library and command line utility tool
sudo apt-get install v4l-utils
sudo apt-get install libv4l-dev

# install librtmp library
sudo apt-get install librtmp-dev

# for cross compilation
sudo apt-get install gcc-arm-linux-gnueabi
sudo apt-get install g++-arm-linux-gnueabi
sudo apt-get install binutils-arm-linux-gnueabi

# on the beaglebone black you may have to replace /etc/init.d/led_aging.sh with the led_aging file in this folder.
# on the beaglebone you also have to run:
# apt-get update
# apt-get install libv4l-dev
# apt-get install librtmp-dev
# echo "deb http://ftp.us.debian.org/debian unstable main contrib non-free" > /etc/apt/sources.list.d/unstable.list
# apt-get install gcc-5
# echo -e "Package: *\nPin: release a=testing\nPin-Priority: 100" > /etc/apt/preferences.d/testing

# might need these
sudo apt-get install libgnutls-dev
sudo apt-get install libssl-dev

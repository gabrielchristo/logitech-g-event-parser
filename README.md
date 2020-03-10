# Logitech g920 socket input event parser
An application who gets the current values of logitech g920 steering wheel and sends to unity3d through udp socket.

For use in linux distros, where the logitech g sdk is not supported.

### Install libevdev
sudo apt-get install libevdev-dev

### Compile source
gcc main.c -I/usr/include/libevdev-1.0 -levdev -omain

### Detect device id
ll /dev/input/by-id or evtest

### Unity StandardAssets Config (used version 2017.3)
replace CarController.cs script on unity standard assets vehicle's folder (and modify it if necessary)


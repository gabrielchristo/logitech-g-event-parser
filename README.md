# Logitech g920 & Gunner Controller - socket input event parser
An application who gets the current values of logitech g920 steering wheel/keyboard and sends to unity3d through udp socket.

For use in linux distros, where the logitech g sdk is not supported.

### Install libevdev
sudo apt-get install libevdev-dev

### Compile and run
execute run.sh 

### Detect device id (3 ways)
> ll /dev/input/by-id

> evtest

> cat /proc/bus/input/devices

### Unity StandardAssets Config (used version 2017.3)
- replace CarController.cs script on unity standard assets vehicle's folder (and modify it if necessary)
- attach the cannon and steeringWheelInputParser scripts to cannon and car objects respectively

### Todo
- fix cannon barrel angle
- read formated log

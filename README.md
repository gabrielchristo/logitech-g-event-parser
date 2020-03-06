# Logitech g920 socket input event parser
An application who gets the current values of logitech g920 steering wheel and sends to unity3d through udp socket.
For use in linux distros, where the logitech g sdk is not supported.

### Install libevdev
sudo apt-get install libevdev-dev

### Compile source
g++ main.cpp -I/usr/include/libevdev-1.0 -levdev -omain

### Detect device id
ll /dev/input/by-id or evtest

### Unity StandardAssets
on CarController.cs script it is necessary to update m_SteerAngle value on Move method.

### ToDo
send whole structure to socket instead of only wheel angle
(de)serialize in unity3ds
/*
 * Logitech G920 Input Event Parser using udp socket
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include <linux/uinput.h>
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 16


typedef struct _steeringWheelData{
	float steeringWheelAngle;
	unsigned char throttle;
	unsigned char brake;
	unsigned char clutch;
	bool leftPaddleShift;
	bool rightPaddleShift;
} steeringWheelData;


steeringWheelData* steeringWheelData_Init(){
	steeringWheelData* d = (steeringWheelData*) malloc(sizeof(steeringWheelData));
	d->steeringWheelAngle = 0.0; // currently -25.0 to 25.0
	d->throttle = 255; // 255 to 0
	d->brake = 255; // 255 to 0
	d->clutch = 255; // 255 to 0
	d->leftPaddleShift = false; // 0 or 1
	d->rightPaddleShift = false; // 0 or 1
	return d;
}


int main(int argc, char** argv){
	
	// data structure init
	steeringWheelData* dataStructure = steeringWheelData_Init();

	// buffer
	char buffer[BUFFER_SIZE];

	// ipv4 server
	struct sockaddr_in remote;
	socklen_t remoteSize = sizeof remote;

	// file descriptor
	int remotefd = socket(AF_INET, SOCK_DGRAM, 0);
	
	// server socket properties	
	remote.sin_family = AF_INET;
	remote.sin_addr.s_addr = inet_addr("127.0.0.1");
	remote.sin_port = htons(PORT);

	// evdev object
	struct libevdev *dev = NULL;
	
	// opening logitech g920 event id
	int fd = open("/dev/input/event7", O_RDONLY|O_NONBLOCK);

	// instance of evdev
	int rc = libevdev_new_from_fd(fd, &dev);

	// printing device name
	fprintf(stdout, "Device name: %s\n", libevdev_get_name(dev));
	
	// socket and wheel event loop
	while(true){
		
		// event object loading (not using yet)
		struct input_event ev;
		rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
	
		// getting normalized values for unity standard assets
		dataStructure->steeringWheelAngle = ((libevdev_get_event_value(dev, EV_ABS, ABS_X) / 32767.5) - 1.0) * 25.0;
		dataStructure->throttle = libevdev_get_event_value(dev, EV_ABS, ABS_Y);
		dataStructure->brake = libevdev_get_event_value(dev, EV_ABS, ABS_Z);
		dataStructure->clutch = libevdev_get_event_value(dev, EV_ABS, ABS_RZ);
		dataStructure->leftPaddleShift = libevdev_get_event_value(dev, EV_KEY, BTN_PINKIE);
		dataStructure->rightPaddleShift = libevdev_get_event_value(dev, EV_KEY, BTN_TOP2);
	
		// connecting to remote udp server
		connect(remotefd, (struct sockaddr *) &remote, remoteSize);

		// reset and updating buffer value
		memset(&buffer, 0x0, BUFFER_SIZE);
		sprintf(buffer, "%f", dataStructure->steeringWheelAngle);

		// sending buffer data
		send(remotefd, buffer, BUFFER_SIZE, 0);

		// printing values
		fprintf(stdout,"\rsteering wheel: %s\tthrottle: %d\tbrake: %d\tclutch: %d\tlps: %d\trps: %d", buffer,	dataStructure->throttle,
																												dataStructure->brake,
																												dataStructure->clutch,
																												dataStructure->leftPaddleShift,
																												dataStructure->rightPaddleShift);

		// sleeping to fixed update
		sleep(0.02);

	}
	
	// free memory
	libevdev_free(dev);

	return 0;
}

/*
 * Logitech G920 & Gunner Controller - Input Event Parser using udp socket
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <future>

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

#include "SteeringWheelData.hpp"
#include "SocketManager.hpp"
#include "GunnerData.hpp"
#include "NonBlockInputHandler.hpp"
#include "LogManager.hpp"

#define IP "127.0.0.1"
#define PORT_WHEEL 5000
#define PORT_GUNNER 5001

int main(int argc, char** argv){
	
	// data structure init
	//SteeringWheelData* wheelData = new SteeringWheelData;
	GunnerData* gunnerData = new GunnerData;

	// steering wheel server
	//UDP_SocketManager* wheelSocket = new UDP_SocketManager;
	//wheelSocket->createIpv4Server(IP, PORT_WHEEL);
	//wheelSocket->connectToServer();

	// gunner server
	UDP_SocketManager* gunnerSocket = new UDP_SocketManager;
	gunnerSocket->createIpv4Server(IP, PORT_GUNNER);
	gunnerSocket->connectToServer();
	
	// evdev init
	//struct libevdev *dev = nullptr;
	//int fileDescriptor = open("/dev/input/event3", O_RDONLY|O_NONBLOCK);
    //int rc = libevdev_new_from_fd(fileDescriptor, &dev);
	
	// printing device name
	//fprintf(stdout, "Device name: %s\n", libevdev_get_name(dev));

	// entering raw mode
	system("stty raw");
	
	// socket event loop
	while(true){
		
		// setups evdev struct to next device event
		//struct input_event ev;
		//rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
	
		// getting normalized values for unity standard assets
		//wheelData->steeringWheelAngle = (float) ((libevdev_get_event_value(dev, EV_ABS, ABS_X) / 32767.5) - 1.0) * 25.0;
		//wheelData->throttle = (float) 1.0 - (libevdev_get_event_value(dev, EV_ABS, ABS_Y) / 255.0);
		//wheelData->brake = (float) 1.0 - (libevdev_get_event_value(dev, EV_ABS, ABS_Z) / 255.0);
		//wheelData->clutch = (float) 1.0 - (libevdev_get_event_value(dev, EV_ABS, ABS_RZ) / 255.0);
		//wheelData->leftPaddleShift = libevdev_get_event_value(dev, EV_KEY, BTN_PINKIE);
		//wheelData->rightPaddleShift = libevdev_get_event_value(dev, EV_KEY, BTN_TOP2);

		// sending struct data pointer
		//wheelSocket->sendData((void*) wheelData, sizeof(wheelData));

		// logging steering wheel data
		//LogManager::log("wheel_log.txt", *wheelData);

		//fprintf(stdout,"\rsteering wheel: %f\tthrottle: %f\tbrake: %f\tclutch: %f\tlps: %d\trps: %d", wheelData->steeringWheelAngle,
		//																							  wheelData->throttle,
		//																							  wheelData->brake,
		//																							  wheelData->clutch,
		//																							  wheelData->leftPaddleShift,
		//																							  wheelData->rightPaddleShift);


		// updating gunner data
		gunnerData->reset();
		std::future<GunnerData*> _future = std::async(NonBlockInputHandler::getCurrentInput, gunnerData);
		// sending empty struct while current value is not returned
		while(_future.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready) gunnerSocket->sendData((void*) gunnerData, sizeof(gunnerData));
        // updating value and sending him
		auto receivedData = _future.get();
		// reseting terminal in case of z key pressed
		if(receivedData == nullptr) system("stty sane");
		// any other key we'll update the data struct and send to unity through socket
		else{
			gunnerData = receivedData;
        	gunnerSocket->sendData((void*) gunnerData, sizeof(gunnerData));
		}

		// logging gunner data
		LogManager::log("gunner_log.txt", *gunnerData);

		fprintf(stdout,"\rUp:%d\t Down:%d\t Left:%d\t Right:%d\t Fire:%d",gunnerData->up,gunnerData->down,gunnerData->left,gunnerData->right,gunnerData->fire);

		// sleeping to fixed update
		//sleep(0.02);

	}
	
	// freeing memory
	//libevdev_free(dev);
	//free(wheelData);
	free(gunnerData);

	return 0;
}

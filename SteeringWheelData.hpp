#pragma once
#pragma pack(1)

struct SteeringWheelData{

	float steeringWheelAngle; // 4 bytes
	float throttle;
	float brake;
	float clutch;
	unsigned char leftPaddleShift; // 1 byte
	unsigned char rightPaddleShift;


    SteeringWheelData(){
        this->steeringWheelAngle = 0.0; // 0 to 65535
	    this->throttle = 255; // 255 to 0
	    this->brake = 255; // 255 to 0
	    this->clutch = 255; // 255 to 0
	    this->leftPaddleShift = false; // 0 or 1
	    this->rightPaddleShift = false; // 0 or 1
    }


};

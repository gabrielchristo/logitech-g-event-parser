#pragma once

#include <iostream>
#include <fstream>
#include <ctime>

#include "GunnerData.hpp"
#include "SteeringWheelData.hpp"

#define SEPARATOR "----------"

class LogManager{

public:

    LogManager();
    ~LogManager();

    static void log(std::string filename, const GunnerData& gunnerData);
    static void log(std::string filename, const SteeringWheelData& steeringWheelData);

private:

    static std::string writeCurrentDateAndHour();

};
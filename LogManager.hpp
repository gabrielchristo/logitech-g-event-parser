#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string.h>
#include <thread>
#include <chrono>
#include <future>

#include "GunnerData.hpp"
#include "SteeringWheelData.hpp"
#include "SocketManager.hpp"

class LogManager{

public:

    LogManager();
    ~LogManager();

    static void log(std::string filename, const GunnerData& gunnerData);
    static void log(std::string filename, const SteeringWheelData& steeringWheelData);

    static void autoSendLog(std::string filename, GunnerData* data, UDP_SocketManager* socket);

private:

    // return current date and hour
    static std::string getCurrentDate();

    // space delimiter by default
    template<class Container> static void splitLineByChar(std::string line, Container& container, char delimiter = ' ');

};
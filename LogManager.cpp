#include "LogManager.hpp"

LogManager::LogManager(){
}

LogManager::~LogManager(){
}


void LogManager::log(std::string filename, const GunnerData& gunnerData){

    std::ofstream outfile;

    // append mode
    outfile.open(filename, std::ios::app);

    // writing separator
    outfile << SEPARATOR << std::endl;

    // writing current date
    outfile << writeCurrentDateAndHour() << std::endl;

    // writing steering wheel properties
    outfile << "up: " << (int) gunnerData.up << std::endl;
    outfile << "down: " << (int) gunnerData.down << std::endl;
    outfile << "left: " << (int) gunnerData.left << std::endl;
    outfile << "right: " << (int) gunnerData.right << std::endl;
    outfile << "fire: " << (int) gunnerData.fire << std::endl;

    // closing file
    outfile.close();

}


void LogManager::log(std::string filename, const SteeringWheelData& steeringWheelData){

    std::ofstream outfile;

    // append mode
    outfile.open(filename, std::ios::app);

    // writing separator
    outfile << SEPARATOR << std::endl;

    // writing current date
    outfile << writeCurrentDateAndHour() << std::endl;

    // writing steering wheel properties
    outfile << steeringWheelData.steeringWheelAngle << std::endl;
    outfile << steeringWheelData.throttle << std::endl;
    outfile << steeringWheelData.brake << std::endl;
    outfile << steeringWheelData.clutch << std::endl;
    outfile << steeringWheelData.leftPaddleShift << std::endl;
    outfile << steeringWheelData.rightPaddleShift << std::endl;

    // closing file
    outfile.close();

}


std::string LogManager::writeCurrentDateAndHour(){

    time_t now = time(0);
    
    return ctime(&now);

}
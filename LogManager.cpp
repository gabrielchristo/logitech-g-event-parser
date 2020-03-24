#include "LogManager.hpp"

LogManager::LogManager(){
}

LogManager::~LogManager(){
}


void LogManager::log(std::string filename, const GunnerData& gunnerData){

    std::ofstream outfile;

    // append mode
    outfile.open(filename, std::ios::app);

    // writing current date
    outfile << "# " << getCurrentDate()
            << " [up  down left right fire]" << std::endl;

    // writing gunner properties
    outfile << (int) gunnerData.up << " "
            << (int) gunnerData.down << " "
            << (int) gunnerData.left << " "
            << (int) gunnerData.right << " "
            << (int) gunnerData.fire << std::endl;

    // closing file
    outfile.close();

}


void LogManager::log(std::string filename, const SteeringWheelData& steeringWheelData){

    std::ofstream outfile;

    // append mode
    outfile.open(filename, std::ios::app);

    // writing current date
    outfile << getCurrentDate() << std::endl;

    // writing steering wheel properties
    outfile << steeringWheelData.steeringWheelAngle << " "
            << steeringWheelData.throttle << " "
            << steeringWheelData.brake << " "
            << steeringWheelData.clutch << " "
            << (int) steeringWheelData.leftPaddleShift << " "
            << (int) steeringWheelData.rightPaddleShift << std::endl;

    // closing file
    outfile.close();

}


std::string LogManager::getCurrentDate(){

    time_t now = time(0);
    // removing break line from ctime char pointer
    return strtok(ctime(&now), "\n");

}


void LogManager::autoSendLog(std::string filename, GunnerData* data, UDP_SocketManager* socket){

    std::ifstream infile;

    // reading mode
    infile.open(filename, std::ios::in);

    // reading line by line
    std::string line;
    while(std::getline(infile, line)){

        // verifying comment line
        if(line.at(0) == '#') continue;

        // updating vector of values
        std::vector<std::string> values;
        splitLineByChar(line, values);
    
        // updating data
        data->up = atoi(values.at(0).c_str());
        data->down = atoi(values.at(1).c_str());
        data->left = atoi(values.at(2).c_str());
        data->right = atoi(values.at(3).c_str());
        data->fire = atoi(values.at(4).c_str());

        // printing values
        //fprintf(stdout,"\rAuto Sending Values -> Up:%u\t Down:%u\t Left:%u\t Right:%u\t Fire:%u", data->up, data->down, data->left, data->right, data->fire);

        // sleeping to get along with unity update
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        // sending data to unity through socket
        socket->sendData((void*) data, sizeof(GunnerData));

        // cleaning data struct
        data->reset();

    }

    // closing file
    infile.close();

}

template<class Container>
void LogManager::splitLineByChar(std::string line, Container& container, char delimiter){

    std::stringstream ss(line);

    std::string temp;

    while(std::getline(ss, temp, delimiter)){
        container.push_back(temp);
    }

}
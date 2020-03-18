#include "NonBlockInputHandler.hpp"

NonBlockInputHandler::NonBlockInputHandler(){
}

NonBlockInputHandler::~NonBlockInputHandler(){
}

GunnerData* NonBlockInputHandler::getCurrentInput(GunnerData* d){

    int asciiCode = (int) getchar();

    switch (asciiCode){
        case 32: // space
            d->fire = 1;
            break;
        case 85: // U
        case 117: // u
            d->up = 1; 
            break;
        case 74: // J
        case 106: // j
            d->down = 1;
            break;
        case 72: // H
        case 104: // h
            d->left = 1;
            break;
        case 75: // K
        case 107: // k
            d->right = 1;
            break;
        case 122: //z
            return nullptr; // returning nullptr to exit raw mode
            break;
    }

    return d;

}
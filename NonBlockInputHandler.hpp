#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "GunnerData.hpp"

class NonBlockInputHandler{

public:

    NonBlockInputHandler();
    ~NonBlockInputHandler();

    static GunnerData* getCurrentInput(GunnerData* d);


};
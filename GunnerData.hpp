#pragma once
#pragma pack(1)

struct GunnerData{

    unsigned char up;
    unsigned char down;
    unsigned char left;
    unsigned char right;
    unsigned char fire;

    GunnerData(){
        this->up = 0;
        this->down = 0;
        this->left = 0;
        this->right = 0;
        this->fire = 0;
    }

    void reset(){
        this->up = 0;
        this->down = 0;
        this->left = 0;
        this->right = 0;
        this->fire = 0;
    }

    bool isZeroData(){
        return (this->up == 0) && (this->down == 0) && (this->left == 0) && (this->right == 0) && (this->fire == 0);
    }

};
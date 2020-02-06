//
//  GlobalVariable.cpp
//  Lab2
//
#include "GlobalVariable.hpp"
int* randval;
int ofs = 0;

int myrandom(int burst) { return 1 + (randval[ofs] % burst); }

void readRandval(ifstream &randomNum){
    char* c = new char[1000];
    randomNum.getline(c, 1000);
    int length = stoi(string(c));
    randval = new int[length+1];
    int i = 0;
    while(!randomNum.eof()){
        randomNum.getline(c, 1000);
        if(randomNum.eof())
            break;
        randval[i] = stoi(string(c));
        i++;
    }
}

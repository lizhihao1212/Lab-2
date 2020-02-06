//
//  GlobalVariable.hpp
//  Lab2

#ifndef GlobalVariable_hpp
#define GlobalVariable_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

extern int ofs;
extern int* randval;
extern int myrandom(int burst);
extern void readRandval(ifstream &randomNum);

#endif /* GlobalVariable_hpp */

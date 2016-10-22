//rankPoint.h
//@author Xinyi,Gong<gongxinyi@wustl.edu>
//This file contains the declarations of a rankPoint object, which saves a hand's rank and its point. 


#ifndef rankPoint_H
#define rankPoint_H

#include <iostream>
#include <string> 


using namespace std;

struct rankPoint {
public:
	double point;
	string handRank;
	rankPoint();
	rankPoint(string s, double r);
	string getHandRank();
	double getPoint();
};


#endif
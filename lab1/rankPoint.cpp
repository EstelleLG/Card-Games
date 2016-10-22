//rankPoint.cpp
//@author Xinyi,Gong<gongxinyi@wustl.edu>
//This file contains the definition of rankPoint functions.


#include "stdafx.h"
#include "rankPoint.h"


rankPoint::rankPoint(){

}
rankPoint::rankPoint(string s, double r) {
	handRank = s;
	point = r;
}

string rankPoint::getHandRank() {
	return handRank;
}

double rankPoint::getPoint(){
	return point;
}

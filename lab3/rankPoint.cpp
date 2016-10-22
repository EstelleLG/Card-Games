//rankPoint.cpp
//@author Xinyi Gong<gongxinyi@wustl.edu> , Yuan Gao<gao.yuan@wustl.edu> , Kunyao Liu<kunyao.liu@wustl.edu>
//

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

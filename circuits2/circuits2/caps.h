#pragma once
#include "complex.h"
class caps //capsitor
{
public:
	double c; //capsitance
	double w; //omiga
	complex z; //imbedince(resistance)
	int pn; //the two
	int nn; //nodes
	caps();
	caps(int pn1,int nn1,double c1,double w1);
	~caps(void);
};


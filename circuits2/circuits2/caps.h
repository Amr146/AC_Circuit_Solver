#pragma once
#include "complex.h"
class caps //capsitor
{
public:
	float c; //capsitance
	float w; //omiga
	complex z; //imbedince(resistance)
	int pn; //the two
	int nn; //nodes
	caps();
	caps(int pn1,int nn1,float c1,float w1);
	~caps(void);
};


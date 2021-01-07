#pragma once
#include "complex.h"
class ind //inductor
{
public:
	float l; //inda
	float w; //omiga
	complex z; //imbedince(resistance)
	int pn; //the two
	int nn; //nodes
	ind(int pn1,int nn1,float l1,float w1);
	~ind(void);
};


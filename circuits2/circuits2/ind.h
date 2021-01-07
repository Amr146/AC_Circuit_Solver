#pragma once
#include "complex.h"
class ind //inductor
{
public:
	double l; //inda
	double w; //omiga
	complex z; //imbedince(resistance)
	int pn; //the two
	int nn; //nodes
	ind(int pn1,int nn1,double l1,double w1);
	~ind(void);
};


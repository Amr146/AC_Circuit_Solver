#pragma once
#include "polar.h"
class ivs //indpendent voltage source
{
public:
	polar p; //value of voltage
	int pn; //positive side
	int nn; //negative side
	ivs();
	ivs(polar p1, int pn1 , int nn1);
	~ivs(void);
};


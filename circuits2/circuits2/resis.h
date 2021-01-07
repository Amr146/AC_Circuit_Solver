#pragma once
#include "complex.h"
class resis
{
public:
	complex c;
	int pn;  //the two
	int nn;  // nodes 
	resis ();
	resis(complex c1,int pn1,int nn1);
	complex getc();
	~resis(void);
};


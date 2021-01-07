#include "resis.h"
#include "complex.h"
resis::resis()
{
	
}
resis::resis(complex c1,int pn1,int nn1)
{
	c=c1;
	pn=pn1;
	nn=nn1;
}
	complex resis:: getc()
	{
		return c;
	}

resis::~resis(void)
{
}

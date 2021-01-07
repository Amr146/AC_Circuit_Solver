#include "resis.h"
#include "complex.h"
resis::resis()
{
	c.real=0;
	c.imag=0;
	pn=0;
	nn=0;
}
resis::resis(complex  c1,int pn1,int nn1)
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

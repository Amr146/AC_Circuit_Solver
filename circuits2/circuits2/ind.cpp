#include "ind.h"
#include "complex.h"

ind::ind(int pn1,int nn1,float l1,float w1)
{
	pn=pn1;
	nn=nn1;
	l=l1;
	w=w1;
	z.real=0;
	z.imag=w*l;
}


ind::~ind(void)
{
}

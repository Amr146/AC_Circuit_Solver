#include "caps.h"
#include "complex.h"
caps::caps(){}
caps::caps(int pn1,int nn1,double c1,double w1)
{
	pn=pn1;
	nn=nn1;
	c=c1;
	w=w1;
	z.real=0;
	z.imag=-1/(w*c);

}


caps::~caps(void)
{
}

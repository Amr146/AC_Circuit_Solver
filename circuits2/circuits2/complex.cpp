#include "complex.h"
#include <cmath>
#include <iostream>
using namespace std;
complex::complex()
{
	real=0;
	imag=0;
}
complex::complex(float r, float i)
{
	real=r;
	imag=i;
}
void complex:: printinfo()
{
	char z;
	if (imag >0)
		z='+';
	else
		z='-';
	cout<<real<<" "<<z<<" "<<abs(imag)<<"j"<<endl;
}
complex complex:: operator+(complex c2)
{
	complex c;
	c.real=real + c2.real;
	c.imag=imag + c2.imag;
	return c;
}
complex complex:: operator-(complex c2)
{
	complex c;
	c.real=real - c2.real;
	c.imag=imag - c2.imag;
	return c;
}
complex::~complex(void)
{
}

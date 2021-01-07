#include "polar.h"
#include <iostream>
#include "complex.h"
using namespace std;
polar::polar()
{
	x=0;
	s=0;
}

polar::polar(float number , float sita)
{
	x=number;
	s=sita;
}
void polar:: printinfo ()
{
	cout<<x<<" "<<s<<endl;
}
void polar:: setx(float x1)
{
	x=x1;
}
	void polar:: sets(float s1)
	{
		s=s1;
	}
	float polar:: getx()
	{
		return x;
	}
	float polar:: gets()
	{
		return s;
	}
polar polar:: operator*(polar p2)
{
	polar p;
	p.x=x*p2.x;
	p.s=s+p2.s;
	return p;
}
polar polar:: operator/(polar p2)
{
	polar p;
	p.x=x/p2.x;
	p.s=s-p2.s;
	return p;
}
polar::~polar(void)
{
}

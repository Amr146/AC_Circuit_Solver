#include "polar.h"
#include <iostream>
#include "complex.h"
using namespace std;
polar::polar()
{
	x=0;
	s=0;
}

polar::polar(double number , double sita)
{
	x=number;
	s=sita;
}
void polar:: printinfo ()
{
	cout<<x<<" "<<s<<endl;
}
void polar:: setx(double x1)
{
	x=x1;
}
	void polar:: sets(double s1)
	{
		s=s1;
	}
	double polar:: getx()
	{
		return x;
	}
	double polar:: gets()
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

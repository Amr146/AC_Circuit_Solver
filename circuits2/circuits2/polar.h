#pragma once
#include "complex.h"
class polar
{
protected:

public:
		double x; //number
	double s; //angle

	polar ();
	polar(double number , double sita);
	void setx(double x1);
	void sets(double s1);
	double getx();
	double gets();
	polar operator*(polar p2);
	polar operator/(polar p2);
	void printinfo ();
	//friend polar fromcomplextopolar(complex c);
	~polar(void);
};


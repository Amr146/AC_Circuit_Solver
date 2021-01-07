#pragma once
#include "complex.h"
class polar
{
protected:

public:
		float x; //number
	float s; //angle

	polar ();
	polar(float number , float sita);
	void setx(float x1);
	void sets(float s1);
	float getx();
	float gets();
	polar operator*(polar p2);
	polar operator/(polar p2);
	void printinfo ();
	//friend polar fromcomplextopolar(complex c);
	~polar(void);
};


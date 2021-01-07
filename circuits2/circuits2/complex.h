#pragma once
class complex
{
protected:
	
public:
	double real;
	double imag;
	complex ();
	complex(double r, double i);
	void printinfo();
	complex operator+(complex c2);
	complex operator-(complex c2);
	void operator+=(complex c2);
//	friend polar fromcomplextopolar(complex c);
	~complex(void);
};


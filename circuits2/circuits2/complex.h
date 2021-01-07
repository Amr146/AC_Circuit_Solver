#pragma once
class complex
{
protected:
	
public:
	float real;
	float imag;
	complex ();
	complex(float r, float i);
	void printinfo();
	complex operator+(complex c2);
	complex operator-(complex c2);
//	friend polar fromcomplextopolar(complex c);
	~complex(void);
};


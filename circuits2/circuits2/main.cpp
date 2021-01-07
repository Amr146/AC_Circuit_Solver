#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <math.h>
#include <cmath>
#include "polar.h"
#include "complex.h"
#include "ivs.h"
#include "resis.h"
#include "caps.h"
#include "ind.h"
#define PI 3.14159265
using namespace std;
polar fromcomplextopolar(complex c) //convert complex number to polar number
{
	polar p;
	p.x=sqrt(c.real*c.real + c.imag*c.imag);
	p.s=(atan(c.imag/c.real)*180)/PI;
	return p;
}
complex frompolartocomplex(polar p)
{
	complex c;
	c.real=cos(p.s*(PI/180))*p.x;
	c.imag=sin(p.s*(PI/180))*p.x;
	return c;
}
int main()
{
	ifstream fin("circuits1.txt");
	string name[11]; //type of component
	string comp[11]; //name of component
	polar * p[11];
	complex * c[11];
	ivs * v[11];
	resis * r[11];
	caps * ca[11];
	ind * in[11];
	int pn[11]; //positive side of source
	int nn[11]; //negative side of source
	int i=1;
	float x[11]; //number of polar
	float s[11]; // sita of polar
	float real[11]; //real part of complex number
	float imag[11]; //imag part of complex number
	float cp[11]; //capasitance
	float l[11]; //indactance
	float w;
	int cvi=0; //num of indpendent voltage source
	int cr=0; //num of resistance
	int cc=0; //num of capasitors
	int ci=0; //num of inductors
	if (fin.is_open())
	{
	for (int k=0; k<11; k++)
	{
		fin>>name[k];
		if (name[k] == "w")
		{
			fin>>w;
			cout<<"omiga = "<<w<<endl;
		}
		if (name[k] == "Vsrc")
		{
			fin>>comp[k]>>pn[k]>>nn[k]>>x[k]>>s[k];
			p[k]=new polar (x[k],s[k]);
			v[k]=new ivs(*p[k],pn[k],nn[k]);
			cout<<"comp number "<<i<<" is indpendent voltage  source"<<endl;
			cvi++;
			i++;
		}
		if (name[k] == "Isrc")
		{
            cout<<"comp number "<<i<<" is independent current source"<<endl;

			i++;
		}
		if (name[k] == "Vcvs")
		{
			 cout<<"comp number "<<i<<" is voltage controlled voltage source"<<endl;

			i++;
		}
		if (name[k] == "Ccvs")
		{
			 cout<<"comp number "<<i<<" is current controlled voltage source"<<endl;

			i++;
		}
		if (name[k] == "Vccs")
		{
			cout<<"comp number "<<i<<" is voltage controlled current source"<<endl;

			i++;
		}
		if (name[k] == "Cccs")
		{
			cout<<"comp number "<<i<<" is current controlled current source"<<endl;

			i++;
		}
	
		if (name[k] == "Res")
		{
			cout<<"comp number "<<i<<" is resistance"<<endl;
					i++;
					fin>>comp[k]>>pn[k]>>nn[k]>>real[k];
					c[k]=new complex (real[k],0);
					r[k]=new resis (*c[k],pn[k],nn[k]);
					cr++;
		}
		if (name[k]== "Cap")
		{
			cout<<"comp number "<<i<<" is capacitance"<<endl;
					i++;
					fin>>comp[k]>>pn[k]>>nn[k]>>cp[k];
					ca[k]=new caps (pn[k],nn[k],cp[k],w);
					cc++;
		}
		if (name[k] == "Ind")
		{
			cout<<"comp number "<<i<<" is inductance"<<endl;
					i++;
					fin>>comp[k]>>pn[k]>>nn[k]>>l[k];
					in[k]=new ind (pn[k],nn[k],l[k],w);
					ci++;
		}

	}
	}
	fin.close();
	complex zt; //total resistance in complex form
	for (int i=0; i<cr; i++)
	{

	   zt=zt+(r[i]->c);
	
	}
	for (int i=0; i<cc; i++)
	{
		zt=zt+(ca[i]->z);
	}
	for (int i=0; i<ci; i++)
	{
		zt=zt+(in[i]->z);
	}
	cout<<"total resistance in complex form = ";
	zt.printinfo();
	polar pt; //total resistance in polar form
	pt=fromcomplextopolar(zt);
	cout<<"total resistance in polar form = ";
	pt.printinfo();
	complex vt; //total voltage in complex form
	
	for (int i=0; i<cvi; i++)
	{
		complex vc;
		vc=frompolartocomplex(v[i]->p);
		vt = vt + vc;
	}
	polar vt2; //total voltage in polar form
	vt2=fromcomplextopolar(vt);

	polar current;
	current = vt2/pt;
	cout<<"current in polar form = ";
	current.printinfo();

}

#include <iostream>
#include <string>
#include <fstream>
//#include <cmath>
#include <Eigen\Dense>

using namespace std;
using namespace Eigen;

/////////////////////////
////	Impedance	////
///////////////////////
struct Impedance{
	double rel, img;
	std::complex<double> z;
	std::complex<double> y;
	Impedance(){
		rel = 0;
		img = 0;
		z.real(rel);
		z.imag(img);
	}

	std::complex<double> getAdmittance(){
		Impedance conj;
		double d = (rel * rel) + (img * img);
		conj.rel = rel/d;
		conj.img = -img/d;
		
		y.real(conj.rel);
		y.imag(conj.img);
		return y;

	}

	std::complex<double> getImpedance(){
		z.real(rel);
		z.imag(img);
		return z;
	}

	Impedance operator + (Impedance z){
		Impedance s;
		s.rel = rel + z.rel;
		s.img = img + z.img;
		return s;
	}

	Impedance operator * (Impedance z){
		Impedance s;
		s.rel = (this->rel * z.rel - this->img * z.img);
		s.img = (this->rel * z.img + this->img * z.rel);
		return s;
	}
	
	Impedance operator ||(Impedance z){
		Impedance p;
		Impedance s = *this + z;
		Impedance m = *this * z;
		Impedance conj;
		conj.rel = s.rel;
		conj.img = -s.img;
		double d = (s.rel * s.rel) + (s.img * s.img);
		p.rel = m.rel/d;
		p.img = m.img/d;
		p = p * conj;
		return p;
	}
}nul;

/////////////////////////
////	Voltage		////
///////////////////////
struct Voltage{
	double rel, img;
	std::complex<double> V;
	
	Voltage(){
		rel = 0;
		img = 0;
		V.real(rel);
		V.imag(img);
	}

	Voltage operator + (Voltage z){
		Voltage s;
		s.rel = rel + z.rel;
		s.img = img + z.img;
		return s;
	}

	Voltage operator * (Voltage z){
		Voltage s;
		s.rel = (this->rel * z.rel - this->img * z.img);
		s.img = (this->rel * z.img + this->img * z.rel);
		return s;
	}

	std::complex<double> getVoltage(){
		V.real(rel);
		V.imag(img);
		return V;

	}
};

/////////////////////////
////	Current		////
///////////////////////
struct Current{
	double rel, img;
	std::complex<double> I;
	
	Current(){
		rel = 0;
		img = 0;
		I.real(rel);
		I.imag(img);
	}

	Current operator + (Current z){
		Current s;
		s.rel = rel + z.rel;
		s.img = img + z.img;
		return s;
	}

	Current operator * (Current z){
		Current s;
		s.rel = (this->rel * z.rel - this->img * z.img);
		s.img = (this->rel * z.img + this->img * z.rel);
		return s;
	}

	std::complex<double> getCurrent(){
		I.real(rel);
		I.imag(img);
		return I;

	}
	void setcurrnt(std::complex<double> c)
	{
		I=c;
		rel=I.real();
		img=I.imag();
	}



};

/////////////////////////
////	Component	////
///////////////////////
class Component{
protected:
	int node1, node2;

public:
	Component(int n1, int n2){ setNodes(n1, n2); }
	void setNodes(int n1, int n2){ node1 = n1;		node2 = n2; }
	int getNode1(){ return node1; }
	int getNode2(){ return node2; }
	virtual Impedance getZ() = 0;
};

/////////////////////////////////////////
////	Independent Voltage Source	////
///////////////////////////////////////
class IndepVolSrc : public Component{
	double Vmax;
	double phi;
	double angularFreq;

public:
	IndepVolSrc(double v, double w, double a, int n1, int n2) : Component(n1, n2){ Vmax = v;	angularFreq = w;		phi = a; }
	double getVmax(){ return Vmax; }
	double getPhi(){ return phi; }
	double getOmiga(){ return angularFreq; }
	Impedance getZ(){ return nul; }
};

/////////////////////////////////////////
////	Independent Current Source	////
///////////////////////////////////////
class IndepCrntSrc : public Component{
	double Imax;
	double phi;
	double angularFreq;

public:
	IndepCrntSrc(double i, double w, double a, int n1, int n2) : Component(n1, n2){ Imax = i;	angularFreq = w;	phi = a; }
	double getImax(){ return Imax; }
	double getPhi(){ return phi; }
	double getOmiga(){ return angularFreq; }
	Impedance getZ(){ return nul; }
};

/////////////////////////
////	Resistor	////
///////////////////////
class Resistor : public Component{
	Impedance z;

public:
	Resistor(double r, int n1, int n2) : Component(n1, n2){ z.rel = r;	z.img = 0; }
	Impedance getZ(){ return z; }
};

/////////////////////////
////	Capacitor	////
///////////////////////
class Capacitor : public Component{
	Impedance z;

public:
	Capacitor(double c, double w, int n1, int n2) : Component(n1, n2){ z.rel = 0;	z.img = -1/(w*c); }
	Impedance getZ(){ return z; }
};

/////////////////////////
////	Inductor	////
///////////////////////
class Inductor : public Component{
	Impedance z;

public:
	Inductor(double l, double w, int n1, int n2) : Component(n1, n2){ z.rel = 0;	z.img = w*l; }
	Impedance getZ(){ return z; }
};

class branch
{
public:
	Impedance impBranch;
	Voltage volt;
	Current amb;
	int node1;
	int node2;
	branch():impBranch(),volt(),amb()
	{
	}
	void printinfo()
	{
		cout<<"Branch ( "<<node1<<" , "<<node2<<" )"<<endl;
		cout<<"Impedance = ";
		cout<<impBranch.getImpedance();
		cout<<endl;
		cout<<"Voltage = ";
		cout<<volt.getVoltage();
		cout<<endl;
		cout<<"Current = ";
		cout<<amb.getCurrent();
		cout<<endl;
	}
	bool isv()
	{
		if(volt.rel==0 && volt.img==0)
			return false;
		else return true;
	}
	bool isimp()
	{
		if(impBranch.rel==0 && impBranch.img==0)
			return false;
		else return true;
	}






};


bool isNonSimpleNode(int *arr, int n, int node);

void analyseComp(Component* pComp, int n1, int n2);

void nodeanalysis();
void VoltToCurrent();

void LoadInputFile(Component*[], int&, string);

class FILE_NOT_FOUND {};


branch B[10];
int n_B=0;
Impedance branchImp[10];				//	Contains The Impedance Of Each Branch
Voltage branchVol[10];					//	Contains The Value Of The Voltage Source In Each Branch -->> if exist
Current branchCrnt[10];					//	Contains The Value Of The Current Source In Each Branch -->> if exist
int x = 0;								//	Index Of The Branch
int numOfConnectedBranchesToNode[5];	//	����� ���� ���� ���
int nonSimpleNodes[6], numOfNonSimpNodes = 0;
int main(){
	Component* arr[10];
	int num = 0;
	string InputFileName;
	while (true)
	{
		cout << "Please, enter the name of the file to " << endl;;
		cin >> InputFileName;
		try
		{
			LoadInputFile(arr, num, InputFileName);
			break;
		}
		catch (FILE_NOT_FOUND)
		{
			cout << "file not found"<<endl;
		}
	}
	
	
	//IndepVolSrc v1(10, 1, -45, 0, 1);
	//double w = v1.getOmiga();
	//arr[num++] = &v1;

	//Resistor r1(3, 1, 2);
	//arr[num++] = &r1;

	//Inductor l1(1, w, 2, 3);
	//arr[num++] = &l1;

	//Resistor r2(4, 3, 4);
	//arr[num++] = &r2;

	//Inductor l2(0.003, w, 3, 5);
	//arr[num++] = &l2;

	//IndepVolSrc v2(5, 1, -60, 0, 3);
	//arr[num++] = &v2;

	//Capacitor c1(1, w, 2, 0);
	//arr[num++] = &c1;

	//IndepCrntSrc i1(3, 1000, 10, 0, 4);
	//arr[num++] = &i1;

	/*IndepVolSrc v1(10, 1000, 0, 0, 1);
	double w = v1.getOmiga();
	arr[num++] = &v1;

	IndepCrntSrc i1(24.616, 1000, 70.26, 3, 0);
	arr[num++] = &i1;

	Resistor r1(20,1, 2);
	arr[num++] = &r1;

	Inductor l1(.01, 1000, 3, 4);
	arr[num++] = &l1;

	Capacitor c1(0.00005, 1000,  2, 3);
	arr[num++] = &c1;

	Resistor r2(20, 2, 0);
	arr[num++] = &r2;

	Resistor r3(30, 4, 0);
	arr[num++] = &r3;*/
	
	//	Getting The Non-Simple Nodes
	
	for(int i = 0; i < num; i++){
		int n1, n2, n3, n4, repeatN1 = 0, repeatN2 = 0;
		n1 = arr[i]->getNode1();
		n2 = arr[i]->getNode2();
		for(int j = i; j < num; j++){
			n3 = arr[j]->getNode1();
			n4 = arr[j]->getNode2();
			if(n1 == n3 || n1 == n4)
				repeatN1++;
			if(n2 == n3 || n2 == n4)
				repeatN2++;
		}
		if(repeatN1 > 2){
			if(!isNonSimpleNode(nonSimpleNodes, numOfNonSimpNodes, n1))
				nonSimpleNodes[numOfNonSimpNodes++] = n1;
		}
		if(repeatN2 > 2){
			if(!isNonSimpleNode(nonSimpleNodes, numOfNonSimpNodes, n2))
				nonSimpleNodes[numOfNonSimpNodes++] = n2;
		}
	}

	int refNode = nonSimpleNodes[0];
	
	for(int i = 1; i < numOfNonSimpNodes; i++)
	{

		for(int j = 0; j < num; j++)
		{
			int n1 = arr[j]->getNode1();
			int n2 = arr[j]->getNode2();
			int startNode;

			if(n2 == nonSimpleNodes[i])
			{
				B[n_B].node1=n2;
				numOfConnectedBranchesToNode[i]++;
				startNode = n1;
				
				analyseComp(arr[j], n1, n2);

				while(!isNonSimpleNode(nonSimpleNodes, numOfNonSimpNodes, startNode))
				{
					for(int k = 0; k < num; k++){
						if(k == j)
							continue;
						n1 = arr[k]->getNode1();
						n2 = arr[k]->getNode2();
						if(startNode == n2)
						{
							startNode = n1;
							analyseComp(arr[k], n1, n2);
							break;
						}
						else if(startNode == n1)
						{
							startNode = n2;
							analyseComp(arr[k], n1, n2);
							break;
						}
					}
				}
				B[n_B++].node2=startNode;
				x++;
			}
			else if(n1 == nonSimpleNodes[i])
			{
				B[n_B].node1=n1;
				numOfConnectedBranchesToNode[i]++;
				startNode = n2;
				
				analyseComp(arr[j], n1, n2);

				while(!isNonSimpleNode(nonSimpleNodes, numOfNonSimpNodes, startNode))
				{
					for(int k = 0; k < num; k++){
						if(k == j)
							continue;
						n1 = arr[k]->getNode1();
						n2 = arr[k]->getNode2();
						if(startNode == n2){
							startNode = n1;
							analyseComp(arr[k], n1, n2);
							break;
						}else if(startNode == n1){
							startNode = n2;
							analyseComp(arr[k], n1, n2);
							break;
						}
					}
				}
				B[n_B++].node2=startNode;
				x++;
			}
		}
	}
	VoltToCurrent();

	for(int i = 0; i < numOfNonSimpNodes; i++)
		cout << nonSimpleNodes[i] << endl;

	cout << "\nImpedence\n";
	for(int i = 0; i < x; i++){
		cout << branchImp[i].getImpedance() << endl;
	}
	cout << "\nAdmittance\n";
	for(int i = 0; i < x; i++){
		cout << branchImp[i].getAdmittance() << endl;
	}
	cout << "\nCurrentSource\n";
	for(int i = 0; i < x; i++){
		cout << branchCrnt[i].getCurrent() << endl;
	}
	cout << "VoltageSource\n";
	for(int i = 0; i < x; i++){
		cout << branchVol[i].getVoltage() << endl;
	}

	for(int i = 1; i < numOfNonSimpNodes; i++){
		cout << numOfConnectedBranchesToNode[i] << endl;
	}

	/*for(int i=0 ;i<numOfConnectedBranchesToNode[2];i++)
		cout << branchImp[i+3].getImpedance() << endl;*/
	for(int i=0;i<n_B;i++)
	{
		B[i].printinfo();
		cout<<endl;
	}
	nodeanalysis();
	system("pause");
	return 0;
}

bool isNonSimpleNode(int *arr, int n, int node){
	for(int i = 0; i < n; i++){
		if(arr[i] == node)
			return true;
	}
	return false;
}

void analyseComp(Component* pComp, int n1, int n2){
	if(dynamic_cast<Resistor*>(pComp) != NULL){
		Resistor* r = dynamic_cast<Resistor*>(pComp);
		branchImp[x] = branchImp[x] + r->getZ();
		B[n_B].impBranch=branchImp[x];
		
	}
	else if(dynamic_cast<Capacitor*>(pComp) != NULL){
		Capacitor* c = dynamic_cast<Capacitor*>(pComp);
		branchImp[x] = branchImp[x] + c->getZ();
		B[n_B].impBranch=branchImp[x];
	}
	else if(dynamic_cast<Inductor*>(pComp) != NULL){
		Inductor* l = dynamic_cast<Inductor*>(pComp);
		branchImp[x] = branchImp[x] + l->getZ();
		B[n_B].impBranch=branchImp[x];
	}
	else if(dynamic_cast<IndepVolSrc*>(pComp) != NULL){
		IndepVolSrc* v = dynamic_cast<IndepVolSrc*>(pComp);
		branchVol[x].rel = v->getVmax()*cos(v->getPhi() * (22.0/7)/180);
		branchVol[x].img = v->getVmax()*sin(v->getPhi() * (22.0/7)/180);
		B[n_B].volt.rel=branchVol[x].rel;
		B[n_B].volt.img=branchVol[x].img;
		
		if(n1 > n2){
			branchVol[x].rel *= -1;
			branchVol[x].img *= -1;
			B[n_B].volt.rel=branchVol[x].rel;
			B[n_B].volt.img=branchVol[x].img;
		}
	}else{
		IndepCrntSrc* v = dynamic_cast<IndepCrntSrc*>(pComp);
		branchCrnt[x].rel = v->getImax()*cos(v->getPhi() * (22.0/7.0)/180.0);
		branchCrnt[x].img = v->getImax()*sin(v->getPhi() * (22.0/7.0)/180.0);
		B[n_B].amb.rel=branchCrnt[x].rel;
		B[n_B].amb.img=branchCrnt[x].img;
		if(n1 > n2){
			branchCrnt[x].rel *= -1;
			branchCrnt[x].img *= -1;
			B[n_B].amb.rel=branchCrnt[x].rel;
			B[n_B].amb.img=branchCrnt[x].img;
		}
	}
}


void nodeanalysis()
{
	int n=numOfNonSimpNodes-1;
	Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic> y(n, n);
	y.setZero();
	Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic> cu(n, 1);
	cu.setZero();
	Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic> R(n, 1);
	R.setZero();
	for(int i=1; i<numOfNonSimpNodes;i++)
	{
		for(int j=0;j<n_B;j++)
		{
			if(B[j].node1==nonSimpleNodes[i] && B[j].node2==0)
			{
				if(B[j].isimp())
					y(i-1,i-1)=y(i-1,i-1)+1.0/B[j].impBranch.getImpedance();
				cu(i-1,0)=cu(i-1,0)+B[j].amb.getCurrent();
			}
			else if(B[j].node1==nonSimpleNodes[i] && B[j].node2!=0)
			{
				for(int k=1; k<numOfNonSimpNodes; k++)
				{
					if(B[j].node2==nonSimpleNodes[k] && i!=k)
					{
						if(B[j].isimp())
							y(i-1,i-1)=y(i-1,i-1)+1.0/B[j].impBranch.getImpedance();
							y(i-1,k-1)=y(i-1,k-1)-1.0/B[j].impBranch.getImpedance();
						cu(i-1,0)=cu(i-1,0)+B[j].amb.getCurrent();
					}

				}

			}

		}

	}
	R=y.inverse()*cu;
	cout<<y<<endl<<endl;
	cout<<cu<<endl<<endl;
	for(int i=1;i<numOfNonSimpNodes;i++)
		cout<<"V"<<nonSimpleNodes[i]<<" = "<<R(i-1,0)<<endl;

}

void VoltToCurrent()
{
	for(int i=0; i<n_B ;i++)
	{
		if(B[i].isv())
		{
			B[n_B].node1=B[i].node1;
			B[n_B].node2=B[i].node2;
			B[n_B].amb.setcurrnt(B[i].volt.getVoltage()/B[i].impBranch.getImpedance());
			n_B++;
			B[i].volt.rel=0;
			B[i].volt.img=0;
		}

	}

}

void LoadInputFile(Component* arr[], int &N,string FileName)
{
	ifstream InputFile("Input\\" + FileName + ".txt");
	if (InputFile.is_open())
	{
		string ComponentType;
		string ComponentName;
		int  n1, n2;
		double value, phi;
		int Omega = 0;
		while (!InputFile.eof())
		{
			InputFile >> ComponentType;

			if (ComponentType == "w")
			{
				InputFile >> value;
				Omega = value;
			}
			else if (ComponentType == "res")
			{
				InputFile >> ComponentName >> n1 >> n2 >> value;
				arr[N++] = new Resistor(value, n1, n2);
			}
			else if (ComponentType == "vsrc")
			{
				InputFile >> ComponentName >> n1 >> n2 >> value >> phi;
				arr[N++] = new IndepVolSrc(value, Omega, phi, n1, n2);
			}
			else if (ComponentType == "isrc")
			{
				InputFile >> ComponentName >> n1 >> n2 >> value >> phi;
				arr[N++] = new IndepCrntSrc(value, Omega, phi, n1, n2);
			}
			else if (ComponentType == "vcvs")
			{
				cout << "voltage controlled voltage source" << endl;
			}
			else if (ComponentType == "cccs")
			{
				cout << "current controlled current source" << endl;
			}
			else if (ComponentType == "cap")
			{
				InputFile >> ComponentName >> n1 >> n2 >> value;
				arr[N++] = new Capacitor(value, Omega, n1, n2);
			}
			else if (ComponentType == "ind")
			{
				InputFile >> ComponentName >> n1 >> n2 >> value;
				arr[N++] = new Inductor(value, Omega, n1, n2);
			}
			else if (ComponentType == "-1")
				break;
		}
	}
	else
		throw FILE_NOT_FOUND ();
}
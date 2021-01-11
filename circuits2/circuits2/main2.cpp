#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

/////////////////////////
////	Impedance	////
///////////////////////
struct Impedance{
	double rel, img;
	
	Impedance(){
		rel = 0;
		img = 0;
	}

	Impedance getAdmittance(){
		Impedance conj;
		if(rel == 0 && img == 0)
			return conj;
		double d = (rel * rel) + (img * img);
		conj.rel = rel/d;
		conj.img = -img/d;
		return conj;
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

	bool operator == (Impedance z){
		return (rel == z.rel && img == z.img);
	}

}nul;

/////////////////////////
////	Current		////
///////////////////////
struct Current{
	double rel, img;
	
	Current(){
		rel = 0;
		img = 0;
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
}nul3;

/////////////////////////
////	Voltage		////
///////////////////////
struct Voltage{
	double rel, img;
	
	Voltage(){
		rel = 0;
		img = 0;
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

	Current operator / (Impedance z){
		Impedance Admitt = z.getAdmittance();
		Current i;
		i.rel = (rel * Admitt.rel - img * Admitt.img);
		i.img = (rel * Admitt.img + img * Admitt.rel);

		return i;
	}

}nul2;

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

bool isNonSimpleNode(int *arr, int n, int node);

void analyseComp(Component* pComp, int n1, int n2);

Impedance branchImp[10];				//	Contains The Impedance Of Each Branch
Voltage branchVol[10];					//	Contains The Value Of The Voltage Source In Each Branch -->> if exist
Current branchCrnt[10];					//	Contains The Value Of The Current Source In Each Branch -->> if exist
int x = 0;								//	Index Of The Branch
int numOfConnectedBranchesToNode[5];	//	«·«”„ ‘«—Õ ‰›”Â ÂÂÂ

int main(){

	Component* arr[10];
	int num = 0;
	
	IndepVolSrc v1(12, 1000, 0, 0, 1);
	double w = v1.getOmiga();
	arr[num++] = &v1;

	Resistor r1(3, 1, 2);
	arr[num++] = &r1;

	Inductor l1(0.002, w, 2, 3);
	arr[num++] = &l1;

	Resistor r2(4, 3, 4);
	arr[num++] = &r2;

	Inductor l2(0.003, w, 3, 5);
	arr[num++] = &l2;

	IndepVolSrc v2(6, 1000, 0, 0, 5);
	arr[num++] = &v2;

	Capacitor c1(0.0005, w, 4, 0);
	arr[num++] = &c1;

	IndepCrntSrc i1(3, 1000, 10, 0, 4);
	arr[num++] = &i1;
	
	//	Getting The Non-Simple Nodes
	int nonSimpleNodes[6], numOfNonSimpNodes = 0;
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
	
	for(int i = 1; i < numOfNonSimpNodes; i++){

		for(int j = 0; j < num; j++){
			int n1 = arr[j]->getNode1();
			int n2 = arr[j]->getNode2();
			int startNode;

			if(n2 == nonSimpleNodes[i]){
				numOfConnectedBranchesToNode[i]++;
				startNode = n1;
				
				analyseComp(arr[j], n1, n2);

				while(!isNonSimpleNode(nonSimpleNodes, numOfNonSimpNodes, startNode)){
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
				x++;
			}else if(n1 == nonSimpleNodes[i]){
				numOfConnectedBranchesToNode[i]++;
				startNode = n2;
				
				analyseComp(arr[j], n1, n2);

				while(!isNonSimpleNode(nonSimpleNodes, numOfNonSimpNodes, startNode)){
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
				x++;
			}
		}
	}

	//	Getting The Coefficient Matrix
	Impedance coefficientMtrx[5][5] = {nul};
	Current constVector[5] = {nul3};
	int n;

	for(int i = 1; i < numOfNonSimpNodes; i++){
		Impedance diagAdmitt;
		Current sumCrnt;
		
		if(i > 1)
			n += numOfConnectedBranchesToNode[i];
		else
			n = numOfConnectedBranchesToNode[i];

		for(static int j = 0; j < n; j++){
			diagAdmitt = diagAdmitt + branchImp[j].getAdmittance();
			sumCrnt = sumCrnt + branchCrnt[j] + (branchVol[j]/branchImp[j]);

			int index1 = i - 1;
			for(int f = 0; f < j; f++){
				if(branchImp[j] == branchImp[f]){
					int limit = n - numOfConnectedBranchesToNode[index1];
					
					while(index1 >= 0){
						if(f < limit){
							Impedance commonAdmitt = branchImp[f].getAdmittance();
							coefficientMtrx[i-1][index1-1].rel += -1 * commonAdmitt.rel;
							coefficientMtrx[i-1][index1-1].img += -1 * commonAdmitt.img;
						}
						index1--;
						limit -= numOfConnectedBranchesToNode[index1];
					}					
				}
			}

			int index2 = i + 1;
			for(int g = n; g < x; g++){
				if(branchImp[j] == branchImp[g]){
					int limit = numOfConnectedBranchesToNode[index2] + n;
					
					while(index2 < numOfNonSimpNodes){
						if(g < limit){
							Impedance commonAdmitt = branchImp[g].getAdmittance();
							coefficientMtrx[i-1][index2-1].rel += -1 * commonAdmitt.rel;
							coefficientMtrx[i-1][index2-1].img += -1 * commonAdmitt.img;
						}
						index2++;
						limit += numOfConnectedBranchesToNode[index2];
					}					
				}
			}
		}
		
		coefficientMtrx[i-1][i-1] = diagAdmitt;		//	Main Diagonal In Coefficient Matrix
		constVector[i-1] = sumCrnt;					//	Vector Of Current
	}


	//	Testing
	for(int i = 0; i < numOfNonSimpNodes-1; i++){
		for(int j = 0; j < numOfNonSimpNodes-1; j++){
			cout << "(" << coefficientMtrx[i][j].rel << ", " << coefficientMtrx[i][j].img << ")\t";
		}
		cout << "||\t(" << constVector[i].rel << ", " << constVector[i].img << ")";
		cout << endl;
	}

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
	}
	else if(dynamic_cast<Capacitor*>(pComp) != NULL){
		Capacitor* c = dynamic_cast<Capacitor*>(pComp);
		branchImp[x] = branchImp[x] + c->getZ();
	}
	else if(dynamic_cast<Inductor*>(pComp) != NULL){
		Inductor* l = dynamic_cast<Inductor*>(pComp);
		branchImp[x] = branchImp[x] + l->getZ();
	}
	else if(dynamic_cast<IndepVolSrc*>(pComp) != NULL){
		IndepVolSrc* v = dynamic_cast<IndepVolSrc*>(pComp);
		branchVol[x].rel = v->getVmax()*cos(v->getPhi() * (22/7)/180);
		branchVol[x].img = v->getVmax()*sin(v->getPhi() * (22/7)/180);
		if(n1 > n2){
			branchVol[x].rel *= -1;
			branchVol[x].img *= -1;
		}
	}else{
		IndepCrntSrc* v = dynamic_cast<IndepCrntSrc*>(pComp);
		branchCrnt[x].rel = v->getImax()*cos(v->getPhi() * (22/7)/180);
		branchCrnt[x].img = v->getImax()*sin(v->getPhi() * (22/7)/180);
		if(n1 > n2){
			branchCrnt[x].rel *= -1;
			branchCrnt[x].img *= -1;
		}
	}
}
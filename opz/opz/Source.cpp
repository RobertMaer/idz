#include<iostream>
#include<string>
#include <vector>
#include<fstream>
#include "stack.h"
using namespace std;

void reversestack(StackList&);
string getErr(int);
bool loadStack(string, StackList&);
vector <string> metod_Deykstra(string, StackList&, StackList&, StackList&, StackList&);
void SALU(vector <string>);
double naturalLog(double);
double exponent(double);


int main()
{
	setlocale(LC_ALL, "Russian");
	StackList stack_R;
	StackList stack_bool;
	StackList stack_select;
	StackList stack_operation;
	
	vector <string> opz;
	string str1("(7+23-5)>12&true&(2>4)&(3=78)&false");
	string str2("(2*3-5<7)&~(2#3)&true&false=true#false");
	string str_52("7+8+8*2");
	cout << str_52<<endl;
	opz = metod_Deykstra(str_52, stack_R, stack_bool, stack_select, stack_operation);
	for (int i = 0; i < opz.size(); i++) {
		cout << opz[i]<<" ";
	}
	cout << endl;
	SALU(opz);

	/*print(stack_R);
	print(stack_bool);
	print(stack_select);
	print(stack_operation);*/

	return 0;
}


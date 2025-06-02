#include "stack.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

string getErr(int);
string schet_1(string a, string b,string op,string str_1,string str_2)
{
	int x1 = stod(a);
	int x2 = stod(b);
	if (op == "+") {
		return to_string(x1 + x2);
	}
	else if (op == "-") {
		return to_string(x1 - x2);
	}
	else if (op == "*") {
		return to_string(x1 * x2);
	}
	else if (op == "/") {
		if (x2 == 0) {
			cout<<getErr(3);
			return "";
		}
		return to_string(x1 / x2);
	}
	else if (op == "^") {
		return to_string(pow(x1,x2));
	}
	else if (op == ">") {
		if (x1 > x2) {
			return str_1;
		}
		else {
			return str_2;
		}
	}
	else if (op == "<") {
		if (x1 < x2) {
			return str_1;
		}
		else {
			return str_2;
		}
	}
}

string schet_2(string a, string b, string op)
{
	if (op == "&") {
		if (a == b && a[0] == 't') {
			return a;
		}
		else if (a[0] == 'f') {
			return a;
		}
		else if (b[0] == 'f') {
			return b;
		}
	}
	else if (op=="!") {
		if (a == b && a[0]=='f') {
			return a;
		}
		else if (a[0]=='t') {
			return a;
		}
		else if (b[0] == 't') {
			return b;
		}
	}
}

string ob(string a, string b, string op, string str_1, string str_2)
{
	if (op == "=") {
		if (a==b) {
			return str_1;
		}
		else {
			return str_2;
		}
	}
	else if (op == "#") {
		if (a != b) {
			return str_1;
		}
		else {
			return str_2;
		}
	}
}


string unitar(string a, string op) 
{
	int x1 = stod(a);
	if (op == "m") {
		return to_string(-x1);
	}
	else if (op == "p") {
		if (x1<0) return to_string(-x1);
		else return to_string(x1);
	}
}

string otr(string a, string op,string str_1,string str_2)
{
	if (a[0] == 'f') return str_1;
	else if (a[0] == 't') return str_2;
}


 
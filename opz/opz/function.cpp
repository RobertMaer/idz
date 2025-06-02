#include "stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;


double naturalLog(double x) {
	if (x <= 0) {
		cerr << "Ошибка: логарифм определен только для положительных чисел." << endl;
		return 0;
	}
	return log(x);
}

double exponent(double x) {
	return exp(x);
}


void reversestack(StackList& st)
{
	StackList st_temp;
	StackList st_temp_2;
	while (!st.empty()) {
		st_temp.push_str(st.top());
		st.pop();
	}

	while (!st_temp.empty()) {
		st_temp_2.push_str(st_temp.top());
		st_temp.pop();
	}

	while (!st_temp_2.empty()) {
		st.push_str(st_temp_2.top());
		st_temp_2.pop();
	}
}

string getErr(int code) {
	ifstream file("errors.txt");

	if (!file) {
		return "Нельязя открыть 'errors.txt'";
	}
	string line;
	int currentCode;
	while (file >> currentCode && getline(file, line)) {
		if (currentCode == code) {
			return line;
		}
	}

	return "Непредвиденная ошибка";
}

/*bool loadStack(string filename, StackList& st) {
	ifstream in(filename, ios::binary);
	if (!in) {
		cout << getErr(1) << ": " << filename << endl;
		return false;
	}

	int value;
	while (in.read(reinterpret_cast<char*>(&value), sizeof(int))) {
		st.push(value);
	}

	if (st.empty()) {
		cout << getErr(2) << endl;
		return false;
	}

	return true;
}*/
#include <iostream>
#include <utility> //swap
#include "sign.h"

using namespace std;

SIGN::SIGN() : first_name(""), last_name(""), sign("") {}
SIGN::SIGN(string n, string f, string s, int b[]) : first_name(n), last_name(f), sign(s) {
	for (int i = 0; i < 3; i++)
		birth[i] = b[i];
}

SIGN::SIGN(const SIGN& tmp) {
	this->first_name = tmp.first_name;
	this->last_name = tmp.last_name;
	this->sign = tmp.sign;
	for (int i = 0; i < 3; i++)
		this->birth[i] = tmp.birth[i];
}

SIGN& SIGN::operator=(const SIGN& tmp) {
	this->first_name = tmp.first_name;
	this->last_name = tmp.last_name;
	this->sign = tmp.sign;
	for (int i = 0; i < 3; i++)
		this->birth[i] = tmp.birth[i];
	return *this;
}

string& SIGN::first_nameAT() { return first_name; }
string& SIGN::last_nameAT() { return last_name; }
string& SIGN::signAT() { return sign; }
int& SIGN::birthAT(int ch) { 
	try {
		if (ch < 1 || ch > 3) throw exception("wrong data");
	}
	catch (const std::exception& exp) { cout << exp.what() << std::endl; ch = 1; }

	switch (ch) {
	case 1:
		return birth[0];
		break;
	case 2:
		return birth[1];
		break;
	case 3:
		return birth[2];
		break;
	}
}
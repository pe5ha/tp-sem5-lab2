#pragma once
#include <fstream>
#include "MyVector.h"

class fileStr {
	std::string pth;
	std::ifstream file;
	std::string txt;
	MyVect <std::string> sentence;


public:
	fileStr();
	fileStr(std::string);
	~fileStr();
	void open(std::string);
	bool read();
	void analysis(std::string);
};
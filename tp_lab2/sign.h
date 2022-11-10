#pragma once

class SIGN {
	std::string first_name, last_name; //имя, фамилия
	std::string sign;		//знак зодиака
	int birth[3] = { 0 };	//дата рождения

public:
	SIGN();
	SIGN(std::string, std::string, std::string, int[]);
	SIGN(const SIGN&);

	SIGN& operator=(const SIGN&);

	std::string& first_nameAT();
	std::string& last_nameAT();
	std::string& signAT();
	int& birthAT(int);
};
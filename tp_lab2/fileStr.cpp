#include <iostream>
#include <string>
#include "fileStr.h"

using namespace std;

fileStr::fileStr() : pth(""), txt("") {}
fileStr::fileStr(string pth_) : pth(pth_), txt("") {
	file.open(pth, ios::in);
	try {
		if (!file.is_open())
			throw exception("file not found");
	}
	catch (exception& exp) { cout << exp.what() << "\n"; system("pause > nul"); }
}
fileStr::~fileStr() { file.close(); }

void fileStr::open(string pth) {
	file.open(pth, ios::in);
	try {
		if (!file.is_open())
			throw exception("file not found");
	}
	catch (exception& exp) { cout << exp.what() << "\n"; system("pause > nul"); }
}

bool fileStr::read() {
	string sent;
	bool er = 0;
	while (!file.eof()) {
		getline(file, sent);
		txt += sent;
	}
	file.seekg(0);
	
	return (txt.length() > 0 ? false : true);
}

void fileStr::analysis(string word) {
	int cursor_beg = 0; //курсор на начало предложения
	int cursor_end = 0; //курсор на конец предложения
	std::string sent;
	int counter = 0;
	for (int i = 0; i < txt.length(); i++) { //считываем текст
		int word_ind = 0;
		for (int j = i; j < txt.length(); j++) {
			if (txt[j] != word[word_ind]) break;
			word_ind++;
			if (word_ind == word.length()) {
				counter++;
				break;
			}
		}
		if (txt[i] == '!' || txt[i] == '?' || txt[i] == '.') { //находим окончание предложения
			cursor_end = i; 

			for (int cur = cursor_beg; cur <= cursor_end; cur++) //переписываем предложение
				sent.push_back(txt[cur]);
			sent.append("["+std::to_string(counter) + "]");
			counter = 0;
			
			cursor_beg = cursor_end + 1;

			if (sent[0] == ' ') //удаляем лишний пробел, если он есть
				sent.erase(0, 1);

			sentence.push_back(sent);

			sent.clear();
		}
	}
	
	//вывод
	for (int i = 0; i < sentence.size(); i++)
		cout << sentence.at(i) << endl;
}

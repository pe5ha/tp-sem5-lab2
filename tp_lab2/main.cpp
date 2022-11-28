#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "sign.h"
#include "stack.h"
#include "fileStr.h"

using namespace std;

void set_sign(stack&);
void menu_output(short); //отрисовка меню
void set_color(WORD color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }
enum colors_ {
	RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
	WHITE = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
};

int main() {

	stack st;
	stack st_copy;
	const string stack_pth = "stack_data.txt";

	menu_output(1);
	char key_tmp; //временный символ
	char key; //опция
	short func = 1; //запуск функции
	bool ENTER_;
	bool exit = false;

	while (!exit) {
		ENTER_ = false;
		key_tmp = _getch();
		key_tmp == 224 ? key = _getch() : key = key_tmp;

		//управление меню
		switch (key) {
		case 80: //вниз
			func++;
			if (func > 13)
				func = 1;
			break;
		case 72: //вверх
			func--;
			if (func < 1)
				func = 13;
			break;
		case 13: //enter
			ENTER_ = true;
			break;
		}
		
		//switch var
		int del_id;
		int sort;
		string sign;
		fileStr t2;
		string task2_pth;

		if (ENTER_) {
			switch (func) {
			case 1:				//добавить sign
				set_sign(st);
				break;
			case 2:				//удалить последний sign
				st = st - 1;
				break;
			case 3:				//удалить несколько последних sign
				cout << "Enter the number to delete\n";
				cin >> del_id;
				st = st - del_id;
				break;
			case 4:				//удалить по индексу
				cout << "Enter the index\n";
				cin >> del_id;
				st -= del_id;
				break;
			case 5:				//сделать копию стека
				st_copy = st;
				break;
			case 6:				//вставить копию стека
				st = st + st_copy;
				break;
			case 7:				//очистить стек
				st = st - st.SIZE() - 1;
				break;
			case 8:				//сохранить в файл
				st.save_to_file(stack_pth);
				break;
			case 9:				//вывести из файла
				st.extract_from_file(stack_pth);
				break;
			case 10:				//сортировка по дню рождения
				cout << "Enter the sort type\n1.Less\n2.Great\n";
				cin >> sort;
				if (sort < 1 || sort > 2)
					break;
				sort == 1 ? st.sort_by_birth(less_) : st.sort_by_birth(great_);
				break;
			case 11:			//сортировка по sign
				cout << "Enter the sign\n";
				cin >> sign;
				st.out_by_sign(sign);
				break;
			case 12:			//task 2
				system("cls");
				cout << "Enter the path to file\n";
				cin >> task2_pth;
				t2.open(task2_pth);
				t2.read();
				t2.analysis();
				system("pause > nul");
				break;
			case 13:
				exit = true;
				break;
			}
		}
		menu_output(func);
		cout << st;
	}
	return 0;
}

void set_sign(stack& st) {
	string n, l, sig;
	int b[3] = {0};

	cout << "Eneter first name: "; cin >> n;
	cout << "Enter last name: "; cin >> l;
	cout << "Enter a sign: "; cin >> sig;
	cout << "Ener the birth (DDMMYYYY): ";
	for (int i = 0; i < 3; i++)
		cin >> b[i];
	SIGN tmp(n, l, sig, b);
	st += tmp;
}

void menu_output(short menu) {
	set_color(WHITE);
	system("cls");

	cout << endl << "====================================\n\n";
	if (menu == 1)
		set_color(RED);
	else set_color(WHITE);
	cout << "Add a sign to stack\n";
	if (menu == 2)
		set_color(RED);
	else set_color(WHITE);
	cout << "Delete the last sign from stack\n";
	if (menu == 3)
		set_color(RED);
	else set_color(WHITE);
	cout << "Delete the last few sign from stack\n";
	if (menu == 4)
		set_color(RED);
	else set_color(WHITE);
	cout << "Delete by index\n";
	if (menu == 5)
		set_color(RED);
	else set_color(WHITE);
	cout << "Copy stack\n";
	if (menu == 6)
		set_color(RED);
	else set_color(WHITE);
	cout << "Insert a copy stack\n";
	if (menu == 7)
		set_color(RED);
	else set_color(WHITE);
	cout << "Clear stack\n";
	if (menu == 8)
		set_color(RED);
	else set_color(WHITE);
	cout << "Save stack to file\n";
	if (menu == 9)
		set_color(RED);
	else set_color(WHITE);
	cout << "Extract stack from file\n";
	if (menu == 10)
		set_color(RED);
	else set_color(WHITE);
	cout << "Sort stack by birth\n";
	if (menu == 11)
		set_color(RED);
	else set_color(WHITE);
	cout << "Sort stack by sign\n";
	if (menu == 12)
		set_color(RED);
	else set_color(WHITE);
	cout << "Task 2(file and string stream)\n";
	if (menu == 13)
		set_color(RED);
	else set_color(WHITE);
	cout << "Exit\n" << endl;
	set_color(WHITE);
}
#include <iostream>
#include "stack.h"
#include "sign.h"

using namespace std;

bool compare_by_date(SIGN, SIGN);
bool compare_str(string, string); //strcmp

stack::stack() : data(NULL), size_(0) {}
stack::stack(int sz) : data(new SIGN[sz]), size_(sz) {}
stack::stack(const stack& tmp) {
	this->size_ = tmp.size_;;
	this->data = new SIGN[tmp.size_];
	for (int i = 0; i < tmp.size_; i++)
		this->data[i] = tmp.data[i];
}
stack::~stack() { delete[] data; }

stack& stack::operator=(const stack& tmp) {
	this->size_ = tmp.size_;
	this->data = new SIGN[tmp.size_];
	for (int i = 0; i < tmp.size_; i++)
		this->data[i] = tmp.data[i];
	return *this;
}

stack stack::operator+(const stack& tmp) {
	int id;
	stack buf;
	buf.size_ = this->size_ + tmp.size_;
	buf.data = new SIGN[buf.size_];
	for (id = 0; id < this->size_; id++)
		buf.data[id] = this->data[id];
	for (int j = 0; j < tmp.size_; j++, id++)
		buf.data[id] = tmp.data[j];
	return buf;
}

stack stack::operator+(const SIGN& s) {
	stack buf;
	buf.size_ = this->size_ + 1;
	buf.data = new SIGN[buf.size_];
	for (int i = 0; i < this->size_; i++)
		buf.data[i] = this->data[i];
	buf.data[buf.size_ - 1] = s;
	return buf;}

stack stack::operator-(int cnt) {
	stack buf;
	try {
		if (this->size_ - cnt < 0)
			throw out_of_range("stack::operator-(int) ? int-CNT<0 -> CNT=0");
	}
	catch (const exception& exp) { cout << exp.what() << endl; cnt = 0; return *this; }
	buf.size_ = this->size_ - cnt;
	buf.data = new SIGN[buf.size_];
	for (int i = 0; i < buf.size_; i++)
		buf.data[i] = this->data[i];
	return buf;
}

stack& operator+=(stack& s, const stack& tmp) {
	stack buf(s);
	delete[] s.data;
	s.size_ = s.size_ + tmp.size_;
	s.data = new SIGN[s.size_];
	int id;
	for (id = 0; id < buf.size_; id++)
		s.data[id] = buf.data[id];
	for (int j = 0; j < (tmp.data == s.data ? tmp.size_ / 2 : tmp.size_); j++, id++)
		s.data[id] = tmp.data[j];
	return s;
}

stack& operator+=(stack& s, const SIGN val) {
	stack buf(s);
	delete[] s.data;
	s.size_ += 1;
	s.data = new SIGN[s.size_];
	for (int i = 0; i < buf.size_; i++)
		s.data[i] = buf.data[i];
	s.data[s.size_ - 1] = val;
	return s;
}

stack& operator-=(stack& s, int index) {
	index -= 1;
	try {
		if (index < 0 || index > s.size_)
			throw out_of_range("stack::operator-=(INDEX) ? INDEX out of range -> INDEX = 0");
	}
	catch (const exception& exp) { cout << exp.what() << endl; index = 0; return s; }
	
	stack buf(s);
	delete[] s.data;
	s.size_ -= 1;
	s.data = new SIGN[s.size_];
	
	for (int i = 0, j = 0; j < buf.size_; i++, j++) {
		if (i == index)
			j++;
		s.data[i] = buf.data[j];
	}
	return s;
}

std::ostream& operator<<(std::ostream& out, stack& tmp) {
	for (int i = 0; i < tmp.size_; i++) {
		/*data*/
		out << i+1 << ". " << tmp.data[i].first_nameAT() << " " << tmp.data[i].last_nameAT() << " " <<
			tmp.data[i].signAT() << " ";
		for (int j = 0; j < 2; j++) { /*число.мес€ц*/
			if (tmp.data[i].birthAT(j + 1) / 10 == 0)
				out << "0" << tmp.data[i].birthAT(j + 1) << ".";
			else out << tmp.data[i].birthAT(j + 1) << ".";
		}
		out << tmp.data[i].birthAT(3); /*год*/
		out << endl;
	}
	return out;
}

void stack::info_id(int index) {
	try {
		if (index < 0 || index > size_)
			throw exception("stack::void_info_id(INDEX) ? INDEX<0|INDEX>size : INDEX=0");
	}
	catch (const std::exception& exp) {
		cout << exp.what() << endl; index = 0; return;
	}
	cout << data[index].first_nameAT() << " " << data[index].last_nameAT() << " "
		<< data[index].signAT() << " ";
	for (int j = 0; j < 2; j++) { /*число.мес€ц*/
		if (data[index].birthAT(j + 1) / 10 == 0)
			cout << "0" << data[index].birthAT(j + 1) << ".";
		else cout << data[index].birthAT(j + 1) << ".";
	}
	cout << data[index].birthAT(3); /*год*/
	cout << endl;
}

void stack::save_to_file(std::string pth) {
	ofstream f(pth);
	f << size_ << endl;
	for (int i = 0; i < size_; i++) {
		f << data[i].first_nameAT() << "\n" << data[i].last_nameAT() << "\n" 
			<< data[i].signAT() << "\n";
		for (int j = 0; j < 3; j++)
			f << data[i].birthAT(j + 1) << " ";
		f << "\n";
	}
	f.close();
}

void stack::extract_from_file(std::string pth) {
	ifstream f(pth);
	if (!f.is_open())
		return;
	delete[] data;
	f >> size_;
	data = new SIGN[size_];
	for (int i = 0; i < size_; i++) {
		f >> data[i].first_nameAT() >> data[i].last_nameAT() >> data[i].signAT();
		for (int j = 0; j < 3; j++)
			f >> data[i].birthAT(j + 1);
	}

	f.close();
}

void stack::sort_by_birth(gr gr_) {
	for (int i = 0; i < size_; i++) {
		for (int j = i + 1; j < size_; j++) {
			if (gr_ ? (compare_by_date(data[i], data[j])) : (compare_by_date(data[j], data[i]))) {
				swap(data[i], data[j]);
			}
		}
	}
}

void stack::out_by_sign(std::string cmp) {
	bool find = false;
	for (int i = 0; i < size_; i++)
		if (compare_str(data[i].signAT(), cmp))
			info_id(i), find = true;
	if (!find)
		cout << "Sign " << cmp << " not found" << endl;
	system("pause");
}

int stack::SIZE() { return this->size_; }

bool compare_by_date(SIGN s1, SIGN s2) {
	if (s1.birthAT(3) < s2.birthAT(3)) //year
		return less_;
	else if (s1.birthAT(3) > s2.birthAT(3))
		return great_;
	else if (s1.birthAT(2) < s2.birthAT(2)) //month
		return less_;
	else if (s1.birthAT(2) > s2.birthAT(2))
		return great_;
	else if (s1.birthAT(1) < s2.birthAT(1)) //day
		return less_;
	else return great_;
}

bool compare_str(string s1, string s2) {
	int cnt = 0;
	while (s1[cnt] != '\0' || s2[cnt] != '\0')
		if (s1[cnt] != s2[cnt])
			return false;
		else cnt++;
	return true;
}
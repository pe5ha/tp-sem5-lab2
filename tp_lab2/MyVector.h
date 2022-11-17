#pragma once
#include <iostream>

template <typename type>
class MyVect {
	int size_, cap_;
	type* data;

public:
	MyVect();
	MyVect(int);
	MyVect(int, type);
	MyVect(const MyVect&);
	~MyVect();

	type& at(int);
	type& operator[](int);
	MyVect& operator=(const MyVect&);

	int size();
	int capacity();

	void push_back(type);
	void pop_back();

	void resize(const int);
	void reserve(const int);

	void shrink_to_fit();
	void clear();
	bool empty();

};

template <typename type>
MyVect<type>::MyVect() : size_(0), cap_(0), data(NULL) {}

template <typename type>
MyVect<type>::MyVect(int sz) : size_(sz), cap_(sz), data(new type[cap_]) {
	for (int i = 0; i < size_; i++)
		data[i] = 0;
}

template <typename type>
MyVect<type>::MyVect(int sz, type val) : size_(sz), cap_(sz), data(new type[cap_]) {
	for (int i = 0; i < size_; i++)
		data[i] = val;
}

template <typename type>
MyVect<type>::MyVect(const MyVect& tmp) {
	this->size_ = tmp.size_;
	this->cap_ = tmp.cap_;

	this->data = new type[cap_];

	if (tmp.cap_ >= tmp.size_)
		for (int i = 0; i < size_; i++)
			this->data[i] = tmp.data[i];
}

template <typename type>
MyVect<type>::~MyVect() { delete[] data; }

template <typename type>
type& MyVect<type>::at(int i) {
	if (i < 0 || i > size_ - 1) {
		std::cout << "Error!\n";
		system("pause");
		return data[0];
	}
	return data[i];
}

template<typename type>
type& MyVect<type>::operator[](int i) {
	if (i < 0 || i > size_ - 1) {
		std::cout << "Error!\n";
		system("pause");
		return data[0];
	}
	return data[i];
}

template <typename type>
MyVect<type>& MyVect<type>::operator=(const MyVect& tmp) {
	this->size_ = tmp.size_;
	this->cap_ = tmp.cap_;

	this->data = new type[cap_];

	if (tmp.cap_ >= tmp.size_)
		for (int i = 0; i < size_; i++)
			this->data[i] = tmp.data[i];
	return *this;
}

template <typename type>
int MyVect<type>::size() { return size_; }

template <typename type>
int MyVect<type>::capacity() { return cap_; }

template <typename type>
void MyVect<type>::push_back(type val) {
	if (cap_ == size_) {
		if (cap_ == 0) cap_ = 1;
		cap_ *= 2;

		type* data_tmp = new type[cap_];
		for (int i = 0; i < size_; i++)
			data_tmp[i] = data[i];
		delete[] data;
		data = data_tmp;
	}
	data[size_] = val;
	size_++;
}

template <typename type>
void MyVect<type>::pop_back() {
	if (cap_ >= size_) {
		type* data_tmp = new type[cap_];
		for (int i = 0; i < size_ - 1; i++)
			data_tmp[i] = data[i];
		delete[] data;
		data = data_tmp;
		size_--;
	}
}

template <typename type>
void MyVect<type>::resize(const int n_size) {
	if (n_size == size_) return;

	if (cap_ < n_size) {
		cap_ = n_size;
		type* data_tmp = new type[cap_];
		
		if (n_size < size_)
			for (int i = 0; i < n_size; i++)
				data_tmp[i] = data[i];

		if (n_size > size_) {
			for (int i = 0; i < size_; i++)
				data_tmp[i] = data[i];
			for (int i = size_; i < n_size; i++)
				data_tmp[i] = 0;
		}

		delete[] data;
		data = data_tmp;
		size_ = n_size;
	}

	if (cap_ >= n_size) {
		if (n_size > size_) {
			for (int i = size_; i < n_size; i++)
				data[i] = 0;
			size_ = n_size;
		}

		if (n_size < size_) {
			type* data_tmp = new type[cap_];
			for (int i = 0; i < n_size; i++)
				data_tmp[i] = data[i];
			delete[] data;
			data = data_tmp;
			size_ = n_size;
		}
	}
}

template <typename type>
void MyVect<type>::reserve(const int n_cap) {
	if (n_cap > size_ && n_cap > cap_) {
		cap_ = n_cap;
		type* data_tmp = new type[cap_];

		for (int i = 0; i < size_; i++)
			data_tmp[i] = data[i];
		delete[] data;
		data = data_tmp;
	}
	else return;
}

template <typename type>
void MyVect<type>::shrink_to_fit() {
	cap_ = size_;
	type* data_tmp = new type[cap_];
	for (int i = 0; i < size_; i++)
		data_tmp[i] = data[i];
	delete[] data;
	data = data_tmp;
}

template <typename type>
void MyVect<type>::clear() {
	delete[] data;
	size_ = 0;
	data = new type[cap_];
}

template <typename type>
bool MyVect<type>::empty() { return size_ > 0 ? false : true; }
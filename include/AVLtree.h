#pragma once
#include <iostream>
#include <vector>
#include "Polinom.h"

class AVLtree {
	struct Element {
		string key;
		Polinom value;
		Element(string _key, Polinom _value) : key(_key), value(_value) {}
	};
	vector<Element> data;

public:
	AVLtree() = default;
	void Insert(string key, Polinom value);  // ������� 
	void Delete(string key);                 // �������� �� �����
	Polinom* Find(string key);               // ����� �� �����
};
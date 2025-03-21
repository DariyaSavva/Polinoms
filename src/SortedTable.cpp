#include "SortedTable.h"


void SortedTable::Insert(string key, Polinom value)
{
	if (Find(key)) throw "Key is already exists"; // �������� �� ������� �����
	int size = data.size();
	int min = 0, max = size - 1;
	int posToInsert = size; // �� ��������� ��������� � �����

	// �������� ����� ������� ��� ������� 
	while (min <= max) {
		int midle = min + (max - min) / 2;
		if (data[midle].key < key) min = midle + 1;
		else {
			max = midle - 1;
			posToInsert = midle;
		}
	}

	// ������� � ������ �������
	data.insert(data.begin() + posToInsert, TableLine(key, value));

}

void SortedTable::Delete(string key)
{
	Polinom* ptrToDel = Find(key); // ����� ��������� �� ��������� �������
	if (!ptrToDel) throw "No Element!"; // �������� ������������� ��������
	vector<TableLine> newdata; 
	for (auto& el : data) {
		if (&el.value != ptrToDel) {
			newdata.push_back(el);
		}
	}
	this->data = newdata; // ���������� ������
}

Polinom* SortedTable::Find(string key)
{
	// �������� �����
	int size = data.size();
	int min = 0, max = size - 1;
	while (min <= max) {
		int midle = min + (max - min) / 2;
		if (data[midle].key == key) {
			return &data[midle].value; // ���� ������
		}
		if (data[midle].key < key) {
			min = midle + 1;
		}
		else {
			max = midle - 1;
		}
	}
	return nullptr;
}

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class Hash
{
public:
	Hash();
	~Hash();
	void insert(const string& input);
	void print();
	size_t getHash(size_t n);
	
private:
	// �������, ���������������� � �����������
	void HashingInMD5();
	// ��������� ����� ������� Little-Endian
	void setLenInFormatLE(unsigned long long lenght);
	// ���������� ������ ����� � �����
	void addByte();
	// ���������� �����
	void addNulls();
	// ���������� ����� �� Little-Endian
	void addLenghtToLE();
	// �������������� ����� � 512 ��� � ������ �� 16 ��� �� 32 ����
	int conv512to32();
	// ������� ������ ������
	size_t shiftLeft(size_t x, size_t n);
	// ������� ��� �������� MD5 ����� ������
	void calcBlocks(size_t lenght);

	// ���������� ������� ��� �������
	size_t F(size_t X, size_t Y, size_t Z);
	size_t G(size_t X, size_t Y, size_t Z);
	size_t H(size_t X, size_t Y, size_t Z);
	size_t I(size_t X, size_t Y, size_t Z);

	// 
	size_t* blocks;
	// ����� ������
	unsigned long long len;
	// ������ � ������� ������
	vector<unsigned char> buf;

	// ������
	size_t A;
	size_t B;
	size_t C;
	size_t D;

	// ������ ��������
	size_t T[64];
};


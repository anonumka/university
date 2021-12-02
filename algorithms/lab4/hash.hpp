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
	// Фукнция, подготавливающая к хешированию
	void HashingInMD5();
	// Установка длины формата Little-Endian
	void setLenInFormatLE(unsigned long long lenght);
	// Добавление одного байта в буфер
	void addByte();
	// Добавление нулей
	void addNulls();
	// Добавление нулей до Little-Endian
	void addLenghtToLE();
	// Преобразование блока в 512 бит в массив из 16 бит по 32 бита
	int conv512to32();
	// Функция сдвига вслево
	size_t shiftLeft(size_t x, size_t n);
	// Фукнция для подсчета MD5 через раунды
	void calcBlocks(size_t lenght);

	// Логические функции для раундов
	size_t F(size_t X, size_t Y, size_t Z);
	size_t G(size_t X, size_t Y, size_t Z);
	size_t H(size_t X, size_t Y, size_t Z);
	size_t I(size_t X, size_t Y, size_t Z);

	// 
	size_t* blocks;
	// Длина строки
	unsigned long long len;
	// Вектор с буквами строки
	vector<unsigned char> buf;

	// Буферы
	size_t A;
	size_t B;
	size_t C;
	size_t D;

	// Массив констант
	size_t T[64];
};


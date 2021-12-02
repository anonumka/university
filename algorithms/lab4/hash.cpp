#include "hash.hpp"

Hash::Hash()
{
	len = 0;
    blocks = NULL;

    // Инициализация дополнительных функций
	A = 0x67452301;
	B = 0xEFCDAB89;
	C = 0x98BADCFE;
	D = 0x10325476;

    // Инициализация таблицы констант
	for (auto i = 1; i <= 64; i++)
		T[i - 1] = size_t(pow(2, 32) * abs(sin(double(i))));
}

Hash::~Hash()
{
}

int Hash::conv512to32() {
	auto wSize = buf.size();
	blocks = new size_t[wSize / 4];

	for (size_t i = 0, j = 0; i < wSize; i += 4, j = i / 4)
    {
		blocks[j] = 0;
		blocks[j] += size_t(buf[i]);
		blocks[j] += size_t(buf[i + 1]) << 8;
		blocks[j] += size_t(buf[i + 2]) << 16;
		blocks[j] += size_t(buf[i + 3]) << 24;
	}

	return wSize / 4;
}

size_t Hash::shiftLeft(size_t x, size_t n) 
{
    return (x << n) | (x >> (32 - n));
}

size_t Hash::F(size_t X, size_t Y, size_t Z)
{ 
    return (X & Y) | (~X & Z); 
}

size_t Hash::G(size_t X, size_t Y, size_t Z)
{ 
    return (X & Z) | (~Z & Y); 
}

size_t Hash::H(size_t X, size_t Y, size_t Z)
{ 
    return X ^ Y ^ Z; 
}

size_t Hash::I(size_t X, size_t Y, size_t Z)
{ 
    return Y ^ (~Z | X); 
}

void Hash::calcBlocks(size_t lenght) 
{
    for (auto i = 0; i < lenght; i += 16) {
        auto AA = A, BB = B, CC = C, DD = D;

        //Первый раунд

        A = B + shiftLeft((A + F(B, C, D) + buf[i + 0] + T[0]), 7);
        D = A + shiftLeft((D + F(A, B, C) + buf[i + 1] + T[1]), 12);
        C = D + shiftLeft((C + F(D, A, B) + buf[i + 2] + T[2]), 17);
        B = C + shiftLeft((B + F(C, D, A) + buf[i + 3] + T[3]), 22);

        A = B + shiftLeft((A + F(B, C, D) + buf[i + 4] + T[4]), 7);
        D = A + shiftLeft((D + F(A, B, C) + buf[i + 5] + T[5]), 12);
        C = D + shiftLeft((C + F(D, A, B) + buf[i + 6] + T[6]), 17);
        B = C + shiftLeft((B + F(C, D, A) + buf[i + 7] + T[7]), 22);

        A = B + shiftLeft((A + F(B, C, D) + buf[i + 8] + T[8]), 7);
        D = A + shiftLeft((D + F(A, B, C) + buf[i + 9] + T[9]), 12);
        C = D + shiftLeft((C + F(D, A, B) + buf[i + 10] + T[10]), 17);
        B = C + shiftLeft((B + F(C, D, A) + buf[i + 11] + T[11]), 22);

        A = B + shiftLeft((A + F(B, C, D) + buf[i + 12] + T[12]), 7);
        D = A + shiftLeft((D + F(A, B, C) + buf[i + 13] + T[13]), 12);
        C = D + shiftLeft((C + F(D, A, B) + buf[i + 14] + T[14]), 17);
        B = C + shiftLeft((B + F(C, D, A) + buf[i + 15] + T[15]), 22);

        //Второй раунд

        A = B + shiftLeft((A + G(B, C, D) + buf[i + 1] + T[16]), 5);
        D = A + shiftLeft((D + G(A, B, C) + buf[i + 6] + T[17]), 9);
        C = D + shiftLeft((C + G(D, A, B) + buf[i + 11] + T[18]), 14);
        B = C + shiftLeft((B + G(C, D, A) + buf[i + 0] + T[19]), 20);

        A = B + shiftLeft((A + G(B, C, D) + buf[i + 5] + T[20]), 5);
        D = A + shiftLeft((D + G(A, B, C) + buf[i + 10] + T[21]), 9);
        C = D + shiftLeft((C + G(D, A, B) + buf[i + 15] + T[22]), 14);
        B = C + shiftLeft((B + G(C, D, A) + buf[i + 4] + T[23]), 20);

        A = B + shiftLeft((A + G(B, C, D) + buf[i + 9] + T[24]), 5);
        D = A + shiftLeft((D + G(A, B, C) + buf[i + 14] + T[25]), 9);
        C = D + shiftLeft((C + G(D, A, B) + buf[i + 3] + T[26]), 14);
        B = C + shiftLeft((B + G(C, D, A) + buf[i + 8] + T[27]), 20);

        A = B + shiftLeft((A + G(B, C, D) + buf[i + 13] + T[28]), 5);
        D = A + shiftLeft((D + G(A, B, C) + buf[i + 2] + T[29]), 9);
        C = D + shiftLeft((C + G(D, A, B) + buf[i + 7] + T[30]), 14);
        B = C + shiftLeft((B + G(C, D, A) + buf[i + 12] + T[31]), 20);

        //Третий раунд

        A = B + shiftLeft((A + H(B, C, D) + buf[i + 5] + T[32]), 4);
        D = A + shiftLeft((D + H(A, B, C) + buf[i + 8] + T[33]), 11);
        C = D + shiftLeft((C + H(D, A, B) + buf[i + 11] + T[34]), 16);
        B = C + shiftLeft((B + H(C, D, A) + buf[i + 14] + T[35]), 23);

        A = B + shiftLeft((A + H(B, C, D) + buf[i + 1] + T[36]), 4);
        D = A + shiftLeft((D + H(A, B, C) + buf[i + 4] + T[37]), 11);
        C = D + shiftLeft((C + H(D, A, B) + buf[i + 7] + T[38]), 16);
        B = C + shiftLeft((B + H(C, D, A) + buf[i + 10] + T[39]), 23);

        A = B + shiftLeft((A + H(B, C, D) + buf[i + 13] + T[40]), 4);
        D = A + shiftLeft((D + H(A, B, C) + buf[i + 0] + T[41]), 11);
        C = D + shiftLeft((C + H(D, A, B) + buf[i + 3] + T[42]), 16);
        B = C + shiftLeft((B + H(C, D, A) + buf[i + 6] + T[43]), 23);

        A = B + shiftLeft((A + H(B, C, D) + buf[i + 9] + T[44]), 4);
        D = A + shiftLeft((D + H(A, B, C) + buf[i + 12] + T[45]), 11);
        C = D + shiftLeft((C + H(D, A, B) + buf[i + 15] + T[46]), 16);
        B = C + shiftLeft((B + H(C, D, A) + buf[i + 2] + T[47]), 23);

        //Четвертый раунд

        A = B + shiftLeft((A + I(B, C, D) + buf[i + 0] + T[48]), 6);
        D = A + shiftLeft((D + I(A, B, C) + buf[i + 7] + T[49]), 10);
        C = D + shiftLeft((C + I(D, A, B) + buf[i + 14] + T[50]), 15);
        B = C + shiftLeft((B + I(C, D, A) + buf[i + 5] + T[51]), 21);

        A = B + shiftLeft((A + I(B, C, D) + buf[i + 12] + T[52]), 6);
        D = A + shiftLeft((D + I(A, B, C) + buf[i + 3] + T[53]), 10);
        C = D + shiftLeft((C + I(D, A, B) + buf[i + 10] + T[54]), 15);
        B = C + shiftLeft((B + I(C, D, A) + buf[i + 1] + T[55]), 21);

        A = B + shiftLeft((A + I(B, C, D) + buf[i + 8] + T[56]), 6);
        D = A + shiftLeft((D + I(A, B, C) + buf[i + 15] + T[57]), 10);
        C = D + shiftLeft((C + I(D, A, B) + buf[i + 6] + T[58]), 15);
        B = C + shiftLeft((B + I(C, D, A) + buf[i + 13] + T[59]), 21);

        A = B + shiftLeft((A + I(B, C, D) + buf[i + 4] + T[60]), 6);
        D = A + shiftLeft((D + I(A, B, C) + buf[i + 11] + T[61]), 10);
        C = D + shiftLeft((C + I(D, A, B) + buf[i + 2] + T[62]), 15);
        B = C + shiftLeft((B + I(C, D, A) + buf[i + 9] + T[63]), 21);

        A += AA; B += BB; C += CC; D += DD;
    }
}

void Hash::addByte()
{
	buf.push_back(128);   //2^7 = 1000 0000
}

void Hash::addNulls() 
{
	do
	{
		buf.push_back(0);
	}
	while (buf.size() % 64 != 56);
}

void Hash::addLenghtToLE() 
{
	for (auto i = 7; i >= 0; i--)
		buf.push_back(unsigned char((len >> (i * 8)) & 0xFF));
}

void Hash::setLenInFormatLE(unsigned long long lenght)
{
	len = _byteswap_uint64(lenght * 8);
}

size_t Hash::getHash(size_t n)
{
    size_t hash = 0;
    hash += A % n;
    hash += B % n;
    hash += C % n;
    hash += D % n;
    hash %= n;
    return hash;
}

void hex(size_t num)
{
    for (auto i = 0; i < 4; i++)
    {
        cout << setfill('0') << setw(2) << hex << num % 256;
        num /= 256;
    }
}

void Hash::print()
{
    hex(A);
    hex(B);
    hex(C);
    hex(D);
    cout << endl;
}

void Hash::HashingInMD5()
{
    addByte();
    addNulls();
    addLenghtToLE();
    calcBlocks(conv512to32());
}

void Hash::insert(const string& input)
{
	for (size_t i = 0; i < input.length(); i++)
	{
		buf.push_back(input[i]);
	}
    setLenInFormatLE(input.length());

    HashingInMD5();
}
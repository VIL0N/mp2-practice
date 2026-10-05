// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len) {
    if (len < 0) {
        throw exception("BitLen<=0");
    }
    BitLen = len;
    MemLen = (len+31) / 32;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    };
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen=bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    int MemInd = n / 32;
    return MemInd;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n<0 || n>=BitLen) {
        throw exception("error n");
    }
    TELEM x = (TELEM)1 << n % 32;
    return x;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= BitLen || n<0 ) throw exception("SetBit error n");
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= BitLen || n < 0) throw exception("ClrBit error n");
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));

}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= BitLen || n < 0) throw exception("GetBit error n");
    int res = (pMem[GetMemIndex(n)] & GetMemMask(n)) >> n % 32;
    return res;
}

// битовые операции

const TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf) return *this;

    if (BitLen != bf.BitLen) {
        delete[] pMem;
        pMem = new TELEM[bf.MemLen];
    }
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 0;
    if (this == & bf) return 1;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (*this==bf) return 0;
  return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int k = max(BitLen, bf.BitLen);
    TBitField t(k);
    if (MemLen > bf.MemLen) {
        for (int i = 0; i < bf.MemLen; i++) {
            t.pMem[i] = bf.pMem[i] | pMem[i];
        }
        for (int i = bf.MemLen; i < MemLen; i++) {
            t.pMem[i] = pMem[i];
        }
    }
    else {
        for (int i = 0; i < MemLen; i++) {
            t.pMem[i] = bf.pMem[i] | pMem[i];
        }
        for (int i = MemLen; i < bf.MemLen; i++) {
            t.pMem[i] = bf.pMem[i];
        }
    }
    
    return t;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int k = max(BitLen, bf.BitLen);
    TBitField t(k);
    if (BitLen > bf.BitLen) {
        for (int i = 0; i < bf.MemLen; i++) {
            t.pMem[i] = bf.pMem[i] & pMem[i];
        }
    }
    else {
         for (int i = 0; i < MemLen; i++) {
            t.pMem[i] = bf.pMem[i] & pMem[i];
         }
    }
    return t;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField t(BitLen);
    for (int i = 0; i < BitLen; i++) {
        if (GetBit(i) == 0) {
            t.SetBit(i);
        }
    }
    return t;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int k;
    istr >> k;
    bf = TBitField(k);

    for (int i = 0; i < bf.MemLen; i++) {
        istr >> bf.pMem[i];
        if ((i == bf.MemLen - 1) && (k % 32 != 0) && (bf.pMem[i] >= ((TELEM)1 << (k % 32))) )
            throw exception("error");
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i) <<' ';
    }
    return ostr;
}

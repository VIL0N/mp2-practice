// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    TBitField tmp(this->GetMaxPower());
    for (int i = 0; i < tmp.GetLength(); i++) {
        if (this->IsMember(i) == 1) tmp.SetBit(i);
    }
    return tmp;
}

int TSet::GetMaxPower(void) const 
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem >= this->GetMaxPower()) throw exception("error");
    if (BitField.GetBit(Elem) == 1)  return 1;
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

const TSet& TSet::operator=(const TSet &s)// присваивание
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower == s.MaxPower) {
        if (BitField == s.BitField) {
            return 1;
        }
    }
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower == s.MaxPower) {
        if (BitField == s.BitField) {
            return 0;
        }
    }
    return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int k = max(MaxPower, s.MaxPower);
    TSet tmp(k);
    tmp = BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem) {// объединение с элементом 
    if (Elem >= MaxPower) throw exception("error elem");
    TSet tmp(Elem+1);
    tmp.BitField.SetBit(Elem);
    tmp = *this + tmp;
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem >= MaxPower) throw exception("error elem");
    TSet tmp(*this);
    if (Elem < MaxPower) {
        tmp.DelElem(Elem);
    }
    return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TBitField tmp(this->BitField & s.BitField);
    return tmp;
}

TSet TSet::operator~(void) // дополнение а тут что?
{
    TBitField tmp(*this);

    for (int i = 0; i < tmp.GetLength(); i++) {
        if (this->IsMember(i) == 1) tmp.ClrBit(i);
        else tmp.SetBit(i);
    }
    TSet tmp1(tmp);
    return tmp1;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int mp;
    istr >> mp;
    s = TSet (mp);
    for (int i = 0; i < mp; i++) {
        bool elem;
        istr >> elem;
        if (elem == 1) s.InsElem(i);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.GetMaxPower(); i++) {
        ostr << s.IsMember(i) << " ";
    }
    return ostr;
}

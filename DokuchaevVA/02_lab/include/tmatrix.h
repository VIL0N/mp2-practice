// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__
#include <cassert>
#include <iostream>

using namespace std;
const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if ((sz == 0)||(sz>MAX_VECTOR_SIZE))
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert((arr != nullptr) && ("TDynamicVector ctor requires non-nullptr arg"));
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  //конструктор копирования 
  TDynamicVector(const TDynamicVector& v) {
      sz = v.sz;
      pMem = new T[sz];
      for (size_t i = 0; i < sz;i++) {
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept //move
  {
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()//деструктор
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)//присваивание
  {
      if (this == &v) {
          return *this;
      }
      if (sz != v.sz) {
          T* tmp = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = tmp;
      }
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
      return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept //присваивание rvalue
  {
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; } //метод размер

  // индексация
  T& operator[](size_t ind) //изменять
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const //только читать
  {
      return pMem[ind];
  }
  // индексация с контролем

  T& at(size_t ind) {
      if (ind > (size() - 1)) throw std::exception ("ind > size-1");
      return pMem[ind];
  }
  const T& at(size_t ind) const {
      if (ind > (size () - 1)) throw std::exception ("ind > size-1");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept //
  {
      if (this == &v) {
          return 1;
      }
      if (sz != v.sz) {
          return 0;
      }
      for (size_t i = 0; i < sz;i++) {
          if (pMem[i] != v.pMem[i]) {
              return 0;
          }
      }
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)//прибавить число
  {
      TDynamicVector tmp(*this);
      for (int i = 0; i < size(); i++) {
          tmp[i] += val;
      }
      return tmp;
  }
  TDynamicVector operator-(T val)//убавить число
  {
      TDynamicVector tmp(*this);
      for (int i = 0; i < size(); i++) {
          tmp[i] -= val;
      }
      return tmp;
  }
  TDynamicVector operator*(T val)//умножить на число
  {
      TDynamicVector tmp(*this);
      for (int i = 0; i < size(); i++) {
          tmp[i] *= val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)//прибавить вектор
  {
      TDynamicVector tmp(*this);
      if (v.sz != sz) {
          throw std::exception ("size !=");
      }
      for (int i = 0; i < size(); i++) {
          tmp[i] += v[i];
      }
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)//вычесть вектор
  {
      TDynamicVector tmp(*this);
      if (v.sz != sz) {
          throw std::exception ("size !=");
      }
      for (int i = 0; i < size(); i++) {
          tmp[i] -= v[i];
      }
      return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          throw std::exception("size!=");
      }
      T tmp = 0;
      for (int i = 0; i < sz; i++) {
          tmp += v[i] * pMem[i];
      }
      return tmp;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept //обмен инфой
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if ((s > MAX_MATRIX_SIZE) || s <= 0) throw std::exception("size><");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz-i);
  }
  TDynamicMatrix(size_t s, const T& t) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if ((s > MAX_MATRIX_SIZE) || s <= 0) throw std::exception("size><");
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = TDynamicVector<T>(sz - i);
          for (size_t j = 0; j < sz-i; j++) {
              pMem[i][j] = t;
          }
      }
  }
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;


  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this == &m) {
          return 1;
      }
      if (sz != m.sz) {
          return 0;
      }
      for (int i = 0; i < sz; i++) {
          if (m[i] != pMem[i]) return 0;
      }
      return 1;

  }
  size_t size() {
      return (*this).sz;
  }
  size_t size() const {
      return (*this).sz;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix tmp(*this);
      for (int i = 0; i < size(); i++) {
          tmp.pMem[i] = tmp.pMem[i] * val;
      }
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.size() != size()) throw std::exception("size NE");
      TDynamicVector<T> tmp(size());
      T tmp2 = 0 ;
      for (size_t i = 0; i < size(); i++) {
          for (size_t j = 0; j < size()-i; j++) {
              tmp2 += pMem[i][j] * v[j+i];
          }
          tmp[i] = tmp2;
          tmp2 = 0;
      }
      return tmp;
  }

  // матрично-векторные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (m.size() != size()) throw std::exception("size NE");
      TDynamicMatrix<T> tmp(size());
      for (size_t i = 0; i < size(); i++) {
          tmp.pMem[i] = pMem[i] + m[i];
      }
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (m.size() != size()) throw std::exception("size NE");
      TDynamicMatrix<T> tmp(size());
      for (size_t i = 0; i < size(); i++) {
          tmp.pMem[i] = pMem[i] - m[i];
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (m.size() != size()) throw std::exception("size NE");
      TDynamicMatrix<T> tmp(size());
      T tmp2 = 0;
      for (size_t i = 0; i < size(); i++) //строки
      {
          for (size_t j = i; j < size(); j++)//столбцы
          {
              for (size_t k = i; k <= j; k++)//столбца х2 для запоминания и выч
              {
                  tmp2 = tmp2 + (pMem[i][k-i] * m[k][j-k]);
              }
              tmp[i][j-i] = tmp2;
              tmp2 = 0;
          }
      }
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.size(); i++) {
          istr >> v[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.size(); i++) {
          for (int j = 0; j < v.size(); j++) {
              if (j >= i) {
                  ostr << v[i][j - i]<<" ";
              }
              else ostr << 0 << " ";
          }
          ostr << "\n";
      }
      return ostr;
  }
};

#endif

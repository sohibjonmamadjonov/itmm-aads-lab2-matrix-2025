// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector {
protected:
  size_t sz;
  T* pMem;

public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0) 
        throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();
  }

  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    copy(arr, arr + sz, pMem);
  }

  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      if (sz == 0) {
          pMem = nullptr;
          return;
      }
      pMem = new T[sz];
      for (size_t i = 0; i < sz; ++i) {
          pMem[i] = v.pMem[i];
      } 
  }

  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
  }

  ~TDynamicVector()
  {
      // проверка на нольптр
      delete[] pMem;
      // присвоить 0 
  }

  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;

      if (v.sz == 0) {
          delete[] pMem; // если уже пусто??
          pMem = nullptr;
          sz = 0;
          return *this;
      }
      // Если память равна?
      T* newMem = new T[v.sz];
      for (size_t i = 0; i < v.sz; i++) {
          newMem[i] = v.pMem[i];
      }

      delete[] pMem;
      pMem = newMem;
      sz = v.sz;

      return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) return *this;
      //?
      delete[] pMem;

      pMem = v.pMem;
      sz = v.sz;

      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }

  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }

  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) throw out_of_range("Index out of range");
      return pMem[ind];
  }

  const T& at(size_t ind) const
  {
      if (ind >= sz) throw out_of_range("Index out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; ++i) {
          if (!(pMem[i] == v.pMem[i])) return false;
      }
      return true;
  }

  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; ++i) {
          result[i] = pMem[i] + val;
      }
      return result;
  }

  TDynamicVector operator-(T val)
  {
      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; ++i) {
          result[i] = pMem[i] - val;
      }
      return result;
  }

  TDynamicVector operator*(T val)
  {
      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; ++i) {
          result[i] = pMem[i] * val;
      }
      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw out_of_range("Vectors are of different sizes");
      if (sz == 0) return TDynamicVector(*this);

      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; ++i) {
          result[i] = pMem[i] + v.pMem[i];
      }
      return result;
  }

  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw out_of_range("Vectors are of different sizes");
      if (sz == 0) return TDynamicVector(*this);

      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; ++i) {
          result[i] = pMem[i] - v.pMem[i];
      }
      return result;
  }

  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      // скалярное умножение двух векторов
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; 
    return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
      for (size_t i = 0; i < v.sz; ++i) {
          ostr << v.pMem[i];
          if (i + 1 < v.sz) ostr << ' '; 
      }                                     
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
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      for (size_t i = 0; i < sz; ++i) {
          if (!(pMem[i] == m.pMem[i])) return false;
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      for (size_t i = 0; i < sz; ++i) {
          pMem[i] *= val;
      }
      return *this;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size()) throw out_of_range("Matrix and vector sizes are incompatible");

      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; ++i) {
          result[i] = pMem[i] * v;
      }
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw out_of_range("Matrices have different sizes");

      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; ++i) {
          result.pMem[i] = pMem[i] + m.pMem[i];
      }

      return result;

  }

  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw out_of_range("Matrices have different sizes");

      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; ++i) {
          result.pMem[i] = pMem[i] - m.pMem[i];
      }

      return result;

  }

  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw out_of_range("Matrices have different sizes");

      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; ++j) {
              T sum = T();
              for (size_t k = 0; k < sz; k++) {
                  sum += pMem[i][k] * m.pMem[k][j];
              }
              result.pMem[i][j] = sum;
          }
      }
      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; ++i) {
          istr >> v.pMem[i];
      }
      return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; ++i) {
          ostr << v.pMem[i] << '\n';
      }
      return ostr;
  }

};

#endif

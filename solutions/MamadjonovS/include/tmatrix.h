// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <iomanip>

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
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size exceeds maximum allowed");
        pMem = new T[sz](); // Инициализация нулями
    }

    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size exceeds maximum allowed");
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz)
    {
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
    {
        v.sz = 0;
        v.pMem = nullptr;
    }

    ~TDynamicVector()
    {
        delete[] pMem;
        sz = 0;
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v) return *this;

        if (sz != v.sz) {
            T* newMem = new T[v.sz];
            delete[] pMem;
            pMem = newMem;
            sz = v.sz;
        }

        std::copy(v.pMem, v.pMem + sz, pMem);
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this == &v) return *this;

        delete[] pMem;
        sz = v.sz;
        pMem = v.pMem;

        v.sz = 0;
        v.pMem = nullptr;

        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Index out of range in operator[]");
        return pMem[ind];
    }

    const T& operator[](size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index out of range in operator[] const");
        return pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Index out of range in at()");
        return pMem[ind];
    }

    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index out of range in at() const");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; ++i) {
            if (pMem[i] != v.pMem[i]) return false;
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
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] + val;
        }
        return result;
    }

    TDynamicVector operator-(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] - val;
        }
        return result;
    }

    TDynamicVector operator*(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] * val;
        }
        return result;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("Vector sizes must be equal for addition");

        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] + v.pMem[i];
        }
        return result;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("Vector sizes must be equal for subtraction");

        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result.pMem[i] = pMem[i] - v.pMem[i];
        }
        return result;
    }

    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("Vector sizes must be equal for dot product");

        T result = T();
        for (size_t i = 0; i < sz; ++i) {
            result += pMem[i] * v.pMem[i];
        }
        return result;
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
        ostr << "[ ";
        for (size_t i = 0; i < v.sz; i++) {
            ostr << v.pMem[i];
            if (i != v.sz - 1) ostr << ", ";
        }
        ostr << " ]";
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
        if (s > MAX_MATRIX_SIZE)
            throw out_of_range("Matrix size exceeds maximum allowed");

        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    size_t size() const noexcept { return sz; }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at;

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; ++i) {
            if (pMem[i] != m.pMem[i]) return false;
        }
        return true;
    }
 
    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result[i] = pMem[i] * val;
        }
        return result;
    }

    TDynamicMatrix operator+(const T& val) { return *this + TDynamicMatrix(sz) * val; }
    TDynamicMatrix operator-(const T& val) { return *this - TDynamicMatrix(sz) * val; }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
            throw invalid_argument("Matrix columns must equal vector size for multiplication");

        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i) {
            T sum = T();
            for (size_t j = 0; j < sz; ++j) {
                sum += pMem[i][j] * v[j];
            }
            result[i] = sum;
        }
        return result;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Matrix sizes must be equal for addition");

        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result[i] = pMem[i] + m.pMem[i];
        }
        return result;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Matrix sizes must be equal for subtraction");

        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) {
            result[i] = pMem[i] - m.pMem[i];
        }
        return result;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Matrix sizes must be equal for multiplication");

        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) {
            for (size_t j = 0; j < sz; ++j) {
                T sum = T();
                for (size_t k = 0; k < sz; ++k) {
                    sum += pMem[i][k] * m.pMem[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; ++i) {
            for (size_t j = 0; j < m.sz; ++j) {
                istr >> m.pMem[i][j];
            }
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
    {
        ostr << "Matrix " << m.sz << "x" << m.sz << ":\n";
        for (size_t i = 0; i < m.sz; ++i) {
            ostr << "  [ ";
            for (size_t j = 0; j < m.sz; ++j) {
                ostr << setw(6) << m.pMem[i][j];
                if (j != m.sz - 1) ostr << " ";
            }
            ostr << " ]\n";
        }
        return ostr;
    }

     
};

#endif
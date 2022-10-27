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
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz > MAX_VECTOR_SIZE) throw - 1;
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T [sz];
    for (int i = 0; i < sz; i++)
    {
      pMem[i] = v.pMem[i];
    }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    pMem = nullptr;
    swap(*this, v);
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v)
    {
      return *this;
    } 
    else
    {
      TDynamicVector a(v);
      swap(*this, a);
      return *this;
    }
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
 
    swap(*this, v);
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    if ((ind < 0)||(ind > sz)) throw - 1;
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    if ((ind < 0)||(ind >sz)) throw - 1;
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if ((ind < 0) || (ind > sz)) throw - 1;
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if ((ind < 0) || (ind > sz)) throw - 1;
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz) return 0;
    if (this == &v) return 1;
    for (int i = 0; i < sz; i++)
    {
      if (pMem[i] != v.pMem[i]) return 0;
    }
    return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz) return 1;
    if (this == &v) return 0;
    for (int i = 0; i < sz; i++)
    {
      if (pMem[i] != v.pMem[i]) return 1;
    }
    return 0;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector a(sz);
    for (int i = 0; i < sz; i++)
    {
      a[i] = pMem[i] + val;
    }
    return a;
  }
  TDynamicVector operator-(double val)
  {
    TDynamicVector a(sz);
    for (int i = 0;i < sz;i++)
    {
      a[i] = pMem[i] - val;
    }
    return a;
  }
  TDynamicVector operator*(double val)
  {
    TDynamicVector a(sz);
    for (int i = 0; i < sz; i++)
    {
      a[i] = pMem[i] * val;
    }
    return a;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz) throw - 1;
    TDynamicVector a(sz);
    for (int i = 0; i < sz; i++)
    {
      a[i] = pMem[i] + v.pMem[i];
    }
     return a;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz) throw - 1;
    TDynamicVector a(sz);
    for (int i = 0; i < sz; i++)
    {
      a[i] = pMem[i] - v.pMem[i];
    }
    return a;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {

    if (sz != v.sz) throw - 1;
    T sum = 0;
    for (int i = 0; i < sz; i++)
    {
      sum = sum + pMem[i] * v.pMem[i];
    }
    return sum;
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
    if (s > MAX_MATRIX_SIZE) throw - 1;
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  size_t size() { return  TDynamicVector<TDynamicVector<T>>::size(); }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    bool flag = 1;
    if (this == &m) return 1;
    if (sz != m.sz) return 0;

    for (int i = 0; i < sz; i++)
    {
      if (pMem[i] != m.pMem[i])
      {
        flag = 0;
        break;
      }
    }
    return flag;
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
    return TDynamicVector<TDynamicVector<T>>::operator*(val);
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    TDynamicVector a(sz);
    for (int i = 0; i<sz;i++)
    {
      a.pMem[i] = v * pMem[i];
    }
    return a;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (m.sz != sz) throw - 1;
    TDynamicMatrix a(sz);
    for (int i = 0; i < sz; i++)
    {
      a.pMem[i] = pMem[i] + m.pMem[i];
    }

    return a;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (m.sz != sz) throw - 1;
    TDynamicMatrix a(sz);
    for (int i = 0; i < sz; i++)
    {
      a.pMem[i] = pMem[i] - m.pMem[i];
    }

    return a;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    TDynamicMatrix<T> a(m.sz);
    T elem ;
    for (int i = 0; i < m.sz; i++)
    {
      for (int j = 0; j < m.sz; j++)
      {
        for (int k = 0; k < m.sz; k++)
        {
          elem = elem + pMem[i][k] * m.pMem[k][j];
        }
        a.pMem[i][j] = elem;
      }
    }
    return a;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (int i = 0; i < v.sz; i++)
    {
      istr >> v.pMem[i];
    }
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (int i = 0; i < v.sz; i++)
    {
      for (int j = 0; j < v.sz; j++)
      {
        ostr << v.pMem[i][j] << ' ';
      }
      ostr << "\n";
    }

    return ostr;
  }
};

#endif

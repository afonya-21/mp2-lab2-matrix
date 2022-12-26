#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������������ ������ - 
// ��������� ������ �� ������������ ������
template<class T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz <= 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]();// � ���� T �.�. ���������� �� ���������
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        if (v.sz <= 0) throw "size of v <= 0";
        sz = v.sz;
        pMem = new T[sz];
        for (size_t i = 0; i < sz; i++)
            pMem[i] = v.pMem[i];
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
        if (pMem != nullptr)
            delete[] pMem;
        pMem = nullptr;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v)
        {
            if (pMem != nullptr)
            {
                delete[] pMem;
                pMem = nullptr;
                sz = 0;
            }

            if (v.pMem != nullptr && v.sz > 0)
            {
                sz = v.sz;
                pMem = new T[sz];
                for (size_t i = 0; i < sz; i++)
                    pMem[i] = v.pMem[i];
            }
            else
                throw "vector v = nullptr or size = 0";

        }
        return *this;

    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v)
        {
            if (pMem != nullptr)
            {
                delete[] pMem;
                pMem = nullptr;
                sz = 0;
            }

            sz = v.sz;
            pMem = v.pMem;

            v.sz = 0;
            v.pMem = nullptr;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }
    size_t GetSize() { return sz; }

    // ����������
    T& operator[](size_t ind)
    {
        if (pMem == nullptr) throw "pMem = nullptr";
        if (ind < 0 || ind >= sz) throw "the index less or greater than size of vector ";
        else
            return pMem[ind];
    }


    // ���������
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (this == &v)
            return true;
        if (sz != v.sz)
            return false;

        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i])
                return false;
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // ��������� ��������
    TDynamicVector operator+(T val)
    {
        TDynamicVector<T> result(*this);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] + val;
        return result;
    }
    TDynamicVector operator-(double val)
    {
        TDynamicVector<T> result(*this);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] - val;
        return result;
    }
    TDynamicVector operator*(double val)
    {
        TDynamicVector<T> result(*this);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] * val;
        return result;
    }

    // ��������� ��������
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "sizes not equals";
        TDynamicVector<T> result(*this);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] + v.pMem[i];
        return result;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "sizes not equals";
        TDynamicVector<T> result(*this);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] - v.pMem[i];
        return result;
    }

    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz) throw "Different size of TVector's";
        T res = 0;
        if (&v != nullptr)
        {
            for (size_t i = 0; i < sz; i++)
            {
                res = pMem[i] * v.pMem[i];
            }
        }
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ����/�����
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // ��������� ��������>> ��� ���� T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // ��������� ��������<< ��� ���� T
        return ostr;
    }
};

/******************************************************************************************************/
// ������������ �������
// ��������� ������� �� ������������ ������
template<class T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz > MAX_MATRIX_SIZE) throw "GG";
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }
    TDynamicMatrix(const TDynamicVector<TDynamicVector<T> >& mt) :TDynamicVector<TDynamicVector<T>>(mt) {}


    using TDynamicVector<TDynamicVector<T>>::operator[];

    // ���������
    bool operator==(const TDynamicMatrix& mt) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>:: operator==(mt);
    }
    size_t GetSize() { return sz; }
    TDynamicMatrix operator=(const TDynamicMatrix<T>& mt)
    {
        if (this == &mt)
            return *this;
        TDynamicVector<T>* tmp = new TDynamicVector<T>[mt.sz];
        delete[] this->pMem;
        this->pMem = tmp;
        this->sz = mt.sz;
        for (int i = 0; i < this->sz; i++) {
            this->pMem[i] = mt.pMem[i];
        }
        return *this;
    }

    // ��������-��������� ��������
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        TDynamicMatrix<T> result(*this);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = 0;

        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j <= i; j++)
            {
                result.pMem[i] += pMem[i][j] * pMem[i][j];
            }
        return result;
    }


    TDynamicMatrix operator+ (const TDynamicMatrix& mt);
    TDynamicMatrix operator- (const TDynamicMatrix& mt);


    // ����/�����
    friend istream& operator>>(istream& in, TDynamicMatrix& mt)
    {
        for (int i = 0; i < mt.sz; i++)
            in >> mt.pMem[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TDynamicMatrix& mt)
    {
        for (int i = 0; i < mt.sz; i++)
            out << mt.pMem[i] << endl;
        return out;
    }

};

template<typename T>// ���������
TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix& mt)
{
    return TDynamicVector<TDynamicVector<T>>:: operator+(mt);
}
template<typename T>// ���������
TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix& mt)
{
    return TDynamicVector<TDynamicVector<T>>:: operator-(mt);
}


#endif
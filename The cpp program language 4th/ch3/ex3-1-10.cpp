/**************************************************************
* Name     :  ex3-1-10.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.4 : Templates
    3.4.1 : parameterized type

template is a compile-time mechanism
*/


template<typename T>

class Vector {
private :
    // elem points to an array of sz elements of type T
    T* elem;
    int sz;
public :
    // constructor : establish invariant, aquire resources
    Vector(int s);
    // destructor : release resources
    ~Vector() { delete[] elem; }
    // ...

    T& operator[](int i);
    const T& operator[](int i) const;
    int size() const { return sz; }
};


template<typename T>

/*  constructor definition  */
Vector<T>::Vector(int s)
{
    if (s < 0)
    {
        throw negative_size {};
    }

    elem = new T[s];
    sz = s;
}


/*  */
template<typename T>

const T& Vector<T>::operator[](int i) const
{
    if (i < 0 || i >= size())
    {
        throw out_of_range { "Vector::operator[]" };
    }
    return elem[i];
}


// Vector of 200 characters
Vector<char> vc(200);
// Vector of 17 strings
Vector<string> vs(17);
// Vector of 45 lists of integers
Vector<list<int>> vli(45);

// Vector of some strings
void write(const Vector<string>& vs)
{
    for (int i = 0; i != vs.size(); ++i)
    {
        cout << vs[i] << '\n';
    }
}


/*  begin() and end() function  */
template<typename T>

T* begin(Vector<T>& x)
{
    // pointer to first element
    return &x[0];
}


// end() function
template<typename T>
T* end(Vector<T>& x)
{
    // pointer to one-past-last element
    return x.begin() + x.size();
}


// Vector of some strings
void f2(const Vector<string>& vs)
{
    // auto : vs must have begin() and end()
    for (auto& s : vs)
    {
        cout << s << '\n';
    }
}


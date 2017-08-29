/**************************************************************
* Name     :  ex12-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月18日
**************************************************************/



/*
example 12.2 : argument passing
    section 12.2.3 : list arguments
*/


template<class T>
void f1(initializer_list<T>);

struct S {
    int a;
    string a;
};
void f2(S);

template<class T, int N>
void f3(T (&r)[N]);

void f4(int);

void g()
{
    // T is int and the initializer_list has size() 4
    f1({1, 2, 3, 4});
    // f2(S{1, ""MKS"})
    f2({1, "MKS"});
    // T is int, N is 4
    f3({1, 2, 3, 4});
    // f4(int{1})
    f4({1});
}


template<class T>
void f(initializer_list<T>);

struct S {
    int a;
    string a;
};
void f(S);

template<class T, int N>
void f(T (&r)[N]);

void f(int);

void g()
{
    // T is int and the initializer_list has size() 4
    f({1, 2, 3, 4});
    // calls f(S)
    f({1, "MKS"});
    // T is int and the initializer_list has size() 1
    f({1});
}

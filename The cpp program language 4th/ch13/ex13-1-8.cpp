/**************************************************************
* Name     :  ex13-1-8.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月23日
**************************************************************/



/*
example 13.5 : throwing and catching exceptions
*/


// section 13.5.1 : throwing exceptions
class No_copy {
    // prohibit copying
    No_copy(const No_copy&) = delete;
};


class My_error {
    // ...
};

void f(int n)
{
    switch (n) {
        case 0 :
            // ok
            throw My_error {};
        case 1 :
            // error : can't copy a No_copy
            throw No_copy {};
        case 2 :
            // error : My_error is a type, not an object
            throw My_error;
    }
}


void f()
{
    string name {"Byron"};
    try {
        string s = "in";
        g();
    }
    catch (My_error) {
        // ...
    }
}

void g()
{
    string s = "excess";
    {
        string s = "or";
        h();
    }
}

void h()
{
    string s = "not";
    throw My_error {};
    string s2 = "at all";
}


struct Some_error { };

void fct()
{
    // ...
    if (something_wrong) {
        throw Some_error {};
    }
}


struct My_error2 : std::runtime_error {
    const char* what() const noexcept { return "My_error2"; }
};


// throw some exception
void g(int n)
{
    if (n) {
        throw std::runtime_error {"I give up!"};
    }
    else {
        throw My_error2 {};
    }
}


// see what exception g() throws
void f(int n)
{
    try {
        void g(n);
    }
    catch (std::exception& e) {
        cerr << e.what() << '\n';
    }
}


// section 13.5.1.1 : noexcept functions
// may not throw an exception
double compute(double) noexcept;

double compute(double x) noexcept
{
    string s = "Courtney and Anya";
    vector<double> tmp(10);
    // ...
}


// section 13.5.1.2 : the noexcept operator
template<typename T>
void my_fct(T& x) noexcept(Is_pod<T>());

template<typename T>
void call_f(vector<T>& v) noexcept(noexcept(f(v[0])))
{
    for (auto x : v) {
        f(x);
    }
}


template<class T, size_t N>
void swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(*a, *b)));


// section 13.5.1.3 : exception specifications
// may only throw Bad or Worse exceptions
void f(int) throw(Bad, Worse);
// may not throw
void g(int) throw();



/**************************************************************
* Name     :  ex18-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月18日
**************************************************************/



/*
example 18.2 : operator functions
*/


//
void f(complex a, complex b)
{
    // shorthand
    complex c = a + b;
    // explicit call
    complex d = a.operator+(b);
}


// section 18.2.1 binary and unary operators
class x {
public :
    void operator+(int);
    X(int);
};

void operator+(X, X);
void operator+(X, double);

void f(X a)
{
    // a.operator+(1)
    a + 1;
    // ::operator+(X(1), a)
    1 + a;
    // ::operator+(a, 1.0)
    a + 1.0;
}


// members (with implicit this pointer)
class X {
public :
    // prefix unary & (address of)
    X* operator&();
    // binary & (and)
    X operator&(X);
    // postfix increment
    X operator++(int);
    // error : ternary
    X operator&(X, X);
    // error : unary
    X operator/();
};

// nonmember functions :
// prefix unary minus
X operator-(X);
// binary minus
X operator-(X, X);
// postfix decrement
X operator--(X&, int);
// error: no operand
X operator-();
// error : ternary
X operator-(X, X, X);
// error : unary %
X operator%(X);


// section 18.2.2 : predefined meanings for operators
class X {
public :
    // ...
    void operator=(const X&) = delete;
    void operator&() = delete;
    void operator,(const X&) = delete;
    // ...
};

void f(X a, X b)
{
    // error : no operator=()
    a = b;
    // error : no operator&()
    &a;
    // error : no operator,()
    a, b;
}


// section 18.2.3 : operators and user-defined types
// enumation is user-defined type
enum Day {
    sun, mon, tue, wed, thu, fri, sat
};

Day& operator++(Day& d)
{
    return d = (sat == d) ? sun : static_cast<Day>(d + 1);
}


// section 18.2.4 : passing objects
// pass-by-value
void Point::operator+=(Point delta);
// pass-by-reference
Matrix operator+(const Matrix&, const Matrix&);

// return-by-value
Matrix operator+(const Matrix& a, const Matrix& b)
{
    Matrix res {a};
    return res += b;
}

// return-by-reference
Matrix& Matrix::operator+=(const Matrix& a)
{
    if (dim[0] != a.dim[0] || dim[1] != a.dim[1]) {
        throw std::exception("bad Matrix += argument");
    }

    double* p = elem;
    double* q = a.elem;
    double* end = p + dim[0] * dim[1];
    while (p != end) {
        *p++ += *q++;
    }
    return *this;
}


// section 18.2.5 : operators in namespaces
// simplified std
namespace std {
    class string {
        // ...
    };
    class ostream {
        // ...
        // output C-style string
        ostream& operator<<(const char*);
    };
    extern ostream cout;
    // output std::string
    ostream& operator<<(ostream&, const string&);
}   // namespace std

int main()
{
    const char* p = "Hello";
    std::string s = "world";
    std::cout << p << ", " << s << "!\n";
}


X operator!(X);

struct Z {
    // does not hide operator!()
    Z operator!();
    // invoke operator!(X)
    X f(X x)
    {
        /* ... */
        return !x;
    }
    // invoke the built-in ! for ints
    int f(int x)
    {
        /* ... */
        return !x;
    }
};

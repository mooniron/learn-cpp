/**************************************************************
* Name     :  ex20-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年6月26日
**************************************************************/



/*
example 20.3 : class hierachies
*/


class Employee { /* ... */ };
class Manager : public Employee { /* ... */ };
class Director : public Manager { /* ... */ };

// graph structure
class Temporary { /* ... */ };
class Assistant : public Employee { /* ... */ };
class Temp : public Temporary, public Assistant { /* ... */ };
class Consultant : public Temporary, public Manager { /* ... */ };


// section 20.3.1 : type fields
struct Employee {
    enum Empl_type {man, empl};
    Empl_type type;
    Employee() : type {empl} { }
    string first_name, family_name;
    char middle_initial;
    Date hiring_date;
    short department;
    // ...
};

struct Manager : public Employee {
    Manager() { type = man; }
    // people managed
    list<Employee*> group;
    short level;
    // ...
};

void print_employee(const Employee* e)
{
    switch (e->type) {
        case Employee::empl :
            cout << e->family_name << '\t' << e->department << '\n';
            // ...
            break;
        case Employee::man {
            cout << e->family_name << '\t' << e->department << '\n';
            // ...
            const Manager* p = static_cast<const Manager*>(e);
            cout << "level " << p->level << '\n';
            // ...
            break;
        }
    }
}

void print_list(const lit<Employee*>& elist)
{
    for (auto x : elist) {
        print_employee(x);
    }
}

void print_employee(const Employee* e)
{
    cout << e->family_name << '\t' << e->department << '\n';
        // ...
    if (e->type == Employee::man) {
        const Manager* p = static_cast<const Manager*>(e);
        cout << "level " << p->level << '\n';
        // ...
    }
}


// section 20.3.2 : virtual functions
class Employee {
public :
    Employee(const string& name, int dept);
    virtual void print() const;
    // ...
private :
    string first_name, family_name;
    short department;
    // ...
};


void Employee::print() const
{
    cout << family_name << '\t' << department << '\n';
    // ...
}


class Manager : public Employee {
public :
    Manager(const string& name, int dept, int lvl);
    void print() const;
    // ...
private :
    list<Employee*> group;
    short level;
    // ...
};

void Manager::print() const
{
    Employee::print();
    cout << "\tlevel " << level << '\n';
    // ...
}

void print_list(const list<Employee*>& s)
{
    for (auto x : s) {
        x->print();
    }
}

int main()
{
    Employee e {"Brown", 1234};
    Manager m {"Smith", 1234, 2};
    print_list({&e, &m});
}


// section 20.3.3 : explicit qualification
void Manager::print()
{
    // not a virtual call
    Employee::print();
    cout << "\tlevel " << level << '\n';
    // ...
}



// section 20.3.4 : override control
struct B0 {
    void f(int) const;
    virtual void g(double);
};

struct B1 : B0 { /* ... */ };
struct B2 : B1 { /* ... */ };
struct B3 : B2 { /* ... */ };
struct B4 : B3 { /* ... */ };
struct B5 : B4 { /* ... */ };

struct D : B5 {
    // override f() in base class : actually not, hide it.
    void f(int) const;
    // override g() in base class : actually not, hide it.
    void g(int);
    // override h() in base class : no h() in base class
    virtual int h();
};


// section 20.3.4.1 : override
struct D : B5 {
    // error : B0::f() is not virtual
    void f(int) const override;
    // error : B0::g() takes a double argument
    void g(int) override;
    // error : no function h() to override
    virtual int h() override;
};

// ok : if there is a suitable f() to override
void f(int) const noexcept override;
// syntax error
override void f(int) const noexcept;
// syntax error
void f(int) override const noexcept;


class Derived : public Base {
    // ok if Base has a virtual g()
    void f() override;
    // ok if Base has a virtual g()
    void g() override;
};

// error : override out of class
void Derived::f() override
{
    // ...
}

// ok
void g()
{
    // ...
}


// don't this
int override = 7;
struct Dx : Base {
    int override;
    int f() override
    {
        return override + ::override;
    }
};


// section 20.3.4.2 : final
// interface class
struct Node {
    virtual Type type() = 0;
    // ...
};

class If_statement : public Node {
public :
    // prevent further overriding
    Type type() override final;
    // ...
};

class Modified_if_statement : public If_statement {
public :
    // error : If_statement::type() is final
    Type type() override;
    // ...
};

// all virtual member function are final
class For_statement final : public Node {
public :
    Type type() override;
    // ...
};

// error : For_statement is final
class Modified_for_statement : public For_statement {
public :
    Type type() override;
    // ...
};


// cannot be repeated in an out of class definition
class Derived : public Base {
    // ok if Base has a virtual f()
    void f() final;
    // ok if Base has a virtual g()
    void g() final;
    //...
};

// error : final out of class
void Derived::f()
{
    // ...
}

// ok
void g()
{
    // ...
}


// don't this
int final = 7;
struct Dx : Base {
    int final;
    int f() final
    {
        return final + ::final;
    }
};



// section 20.3.5 : using Base Members
struct Base {
    void f(int);
};

struct Derived : Base {
    void f(double);
};

void use(Derived d)
{
    // call Derived::f(double)
    d.f(1);
    Base& br = d;
    // call Base f(int)
    br.f(1);
}

struct D2 : Base {
    // bring all fs from Base into D2
    using Base::f;
    void f(double);
};

void use2(D2 d)
{
    // call D2::f(int), that is Base::f(int)
    d.f(1);
    Base& br = d;
    // call Base::f(int)
    br.f(1);
}

struct B1 {
    void f(int);
};

struct B2 {
    void f(double);
};

struct D : B1, B2 {
    using B1::f;
    using B2::f;
    void f(char);
};

void use(D d)
{
    // call D::f(int), that is B1::f(int)
    d.f(1);
    // call D::f(char)
    d.f('a');
    // call D::f(double), that is B2::f(double)
    d.f(1.0);
}


// section 20.3.5.1 : inheriting constructors
// range check vector
template<class T>
struct Vector : std::vector<T> {
    T& operator[](size_type i)
    {
        check(i);
        return this->elem[i];
    }
    const T& operator[](size_type i) const
    {
        check(i);
        return this->elem(i);
    }

    void check(size_type i)
    {
        if (this->size() < i) {
            throw range_error {"Vector::check() failed"};
        }
    }
};

// error : no initializer-list constructor
Vector<int> v {1, 2, 3, 4, 5, 6};

template<class T>
struct Vector : std::vector<T> {
    // inherit constructors
    using vector<T>::vector;
    // ...
};

// ok : use initializer-list constructor from std::vector
Vector<int> v {1, 2, 3, 5, 8};


struct B1 {
    B1(int) { }
};

struct B2 : B1 {
    // implicitly declares D1(int)
    using B1::B1;
    // string has a default constructor
    string s;
    // we "forgot" to provide for initialization of x
    int x;
};

void test()
{
    // oops : d.x is not initialized
    D1 d {6};
    // error : D1 has no default constructor
    D1 e;
}


struct D1 : B1 {
    D1(int i) : B1(i) { }
    string s;
    int x;
};

struct D1 : B1 {
    // implicitly declares D1(int)
    using B1::B1;
    // note : x is initialized
    int x {0};
};

void test()
{
    // d.x is zero
    D1 d {6};
}


// section 20.3.6 : return type relaxation
class Expr {
public :
    // default constructor
    Expr();
    // copy constructor
    Expr(const Expr&);
    virtual Expr* new_expr() = 0;
    virtual Expr* clone() = 0;
    // ...
};

class Cond : public Expr {
public :
    Cond();
    Cond(const Cond&);
    Cond* new_expr() override
    {
        return new Cond();
    }
    Cond* clone() override
    {
        return new Cond(*this);
    }
    // ...
};

void user(Expr* p)
{
    Expr* p2 = p->new_expr();
    // ...
}

void user2(Cond* pc, Addition* pa)
{
    Cond* p1 = pc->clone();
    Addition* p2 = pa->clone();
    // ...
}

void user3(Cond* pc, Expr* pe)
{
    Cond* p1 = pc->clone();
    // error : Expr::clone() return an Expr*
    Cond* p2 = pe->clone();
    // ...
}



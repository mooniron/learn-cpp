/**************************************************************
* Name     :  ex20-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月2日
**************************************************************/



/*
example 20.6 : pointers to members
*/


// 20.6.1 : pointers to function members

// section 20.6.1 : pointers to function members
class Std_interface {
public :
    virtual void start() = 0;
    virtual void suspend() = 0;
    virtual void resume() = 0;
    virtual void quit() = 0;
    virtual void full_size() = 0;
    virtual void small() = 0;
    virtual ~Std_interface() { }
};

// pointer to member type
using Pstd_mem = void (Std_interface::*)();

void f(Std_interface* p)
{
    // pointer to suspend()
    Pstd_mem s = &Std_interface::suspend;
    // direct call
    p->suspend();
    // call through pointer to member
    p->*s();
}


map<string, Std_interface*> variable;
map<string, Pstd_mem> operation;

void call_member(string var, string oper)
{
    // var.oper()
    (variable[var]->*operation[oper])();
}


class Task {
    // ...
    static void schedule();
};

// ok
void (*p)() = &Task::schedule;
// error : ordinary pointer assigned  to pointer to member
void (Task::*pm)() = &Task::schedule;


// section 20.6.2 : pointers to datamembers
struct C {
    const char* val;
    int i;

    void print(int x)
    {
        cout << val << x << '\n';
    }
    int f1(int);
    void f2();
    C(const char* v)
    {
        val = v;
    }
};

// pointer to member function of C taking an int
using Pmfi = void (C::*)(int);
// pointer to char* data member of C
using Pm = const char* C::*;

void f(C& z1, C& z2)
{
    C* p = &z2;
    Pmfi pf = &C::print;
    Pm pm = &C::val;
    z1.print(1);
    (z1.*pf)(2);
    z1.*pm = "nv1 ";
    p->*pm = "nv2 ";
    z2.print(3);
    (p->*pf)(4);
    // error : return type mismatch
    pf = &C::f1;
    // error : argument type mismatch
    pf = &C::f2;
    // error : type mismatch
    pm = &C::i;
    // error : type mismatch
    pm = pf;
}


// section 20.6.3 : base and derived members
class Text : public Std_interface {
public :
    void start();
    void suspend();
    virtual void print();
private :
    vector s;
};

// ERROR
void (Std_interface::* pmi)() = &Text::print;
// ok
void (Text::*pmt)() = &Std_interface::start;

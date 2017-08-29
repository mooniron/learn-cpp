/**************************************************************
* Name     :  ex5-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.2 : resource management
    5.2.1 : unique_ptr and shared_ptr

the shared_ptr is similar to unique_ptr except that shared_ptrs are copied rather than moved.
the shared object is destroyed when the last of its shared_ptrs is destroyed.
*/


#include <iostream>

using namespace std;


// X* vs.unique_ptr<X>
void f(int i, int j)
{
    // allocate a new X
    X* p = new X;
    // allocate a new X and give its pointer to unique_ptr
    unique_ptr<X> sp {new X};
    // ...
    if (i < 99)
    {
        // may throw an exception
        throw Z {};
        // forget to delete p
    }

    if (j < 77)
    {
        // may return "early"
        return;
        // forget to delete p
    }
    // maythrow an exception
    p->do_something();
    sp->do_something();
    // may throw an exception
    // ...

    // destroy *p
    delete p;
}   // end function f


// solve the problem by not using a pointer and not using new
// use a local bariable
void fm(int i, int j)
{
    X x;
    // ...
}


// passing free store allocated objects in and out of functions
// make an X and immediately give it to a unique_ptr
unique_ptr<X> make_X(int i)
{
    // ...
    // check i, etc.

    return unique_ptr<X> {new X{i}};
}   // end function make_X


// shared_ptr
void fshare(shared_ptr<fstream>);

void gshare(shared_ptr<fstream>);

void user(const string& name, ios_base::openmode mode)
{
    shared_ptr<fstream> fp {new fstream(name, mode)};
    // make sure the file was properly opened
    if (!*fp)
    {
        throw No_file {};
    }   // end if

    f(fp);
    g(fp);
}   // end function user

/**************************************************************
* Name     :  ex13-1-9.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月23日
**************************************************************/



/*
example 13.5 : throwing and catching exceptions
    section 13.5.2 : catching exceptions
*/


void f()
{
    try {
        throw E {};
    }
    catch (H) {
        // when do we get here?
    }
}


void g()
{
    int x1;
    try {
        int x2 = x1;
        // ...
    }
    catch (Error) {
        // ok
        ++x1;
        // error : x2 not in scope
        ++x2;
        int x3 = 7;
        // ...
    }
    catch (...) {
        // error : x3 not in scope
        ++x3;
        // ...
    }
    // ok
    ++x1;
    // error : x2 not in scope
    ++x2;
    // error : x3 not in scope
    ++x3;
}


// section 13.5.2.1 : rethrow
void h()
{
    try {
        // ... code that might throw an exception ...
    }
    catch (std::exception& err) {
        if (can_handle_it_completely) {
            // ... handle it ...
            return;
        }
        else {
            // ... do what can be done here ...
            // rethrow the exception
            throw;
        }
    }
}


// section 13.5.2.2 catch every exception
void m()
{
    try {
        // ... do something ...
    }
    catch (std::exception& err) {
        // handle every standard library exception
        // ... cleanup ...
        throw;
    }
}


void m()
{
    try {
        // ... something ...
    }
    catch (...) {
        // handle every exception
        // ... cleanup ...
        throw;
    }
}


// section 13.5.2.3 : multiple handlers
void f()
{
    try {
        // ...
    }
    catch (std::ios_base::failure) {
        // ... handle any iostream error ...
    }
    catch (std::exception& e) {
        // ... handle any standard library exception ...
    }
    catch (...) {
        // ... handle any other exception ...
    }
}


void g()
{
    try {
        // ...
    }
    catch (...) {
        // ... handle every exception ...
    }
    catch (std::exception& e) {
        // ... handle any standard library ...
    }
    catch (std::bad_cast) {
        // ... handle dynamic_cast failure ...
    }
}


// section 13.5.2.4 function try-blocks
int main()
try {
    // ... do something ...
}
catch (...) {
    // ... handle exception ...
}


class X {
    vector<int> vi;
    vector<string> vs;

    // ...
public :
    X(int, int);
    // ...
};

X::X(int sz1, int sz2)
try
    // construct vi with sz1 ints
    : vi(sz1),
    // construct vs with sz2 strings
    vs(sz2),
{
    // ...
}
catch (std::exception& err) {
    // exceptions thrown for vi and vs are caught here
    // the best way is to rethrow
}


// section 13.5.2.5 termination
// from <exception>
using terminate_handler = void(*)();

// a terminate handler cannot return
[[noreturn]] void my_handler()
{
    // handle termination my way
}

// very!
void dangerous()
{
    terminate_handler old = set_terminate(my_handler);
    // ...
    // restore the old terminate handler
    set_terminate(old);
}


int main()
try {
    // ...
}
catch (const My_error& err)
{
    // ... handle my error ...
}
catch (const std::range_error&) {
    cerr << "range error : Not again!\n";
}
catch (const std::bad_alloc&) {
    cerr << "new ran out of memory\n";
}
catch (...) {
    // ...
}



// section 13.5.3 exceptions and threads
try {
    // ... do the work ...
}
catch (...) {
    prom.set_exception(current_exception());
}

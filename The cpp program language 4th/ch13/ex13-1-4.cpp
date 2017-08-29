/**************************************************************
* Name     :  ex13-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月23日
**************************************************************/



/*
example 13.1 : error handling
    section 13.1.5 : when you can't use exceptions
*/


void f(int n)
{
    my_vector<int> x(n);
    if (x.invalid()) {
        // ... deal with errors ...
    }
    // ...
}

void g(int n)
{
    // return a pair
    auto v = make_vector(n);
    if (v.second) {
        // ... deal with error ...
    }
    auto val = v.first;
    // ...
}



// section 13.1.6 : Hierarchical Error Handling
// call a C function from C++; convert errno to a throw
void callC();
{
    errno = 0;
    c_function();

    if (errno) {
        // ... local cleanup, if possible and necessary
        throw C_blewit(errno);
    }
}


// call a c++ function from c; convert a throw to errno
extern "C" void call_from_C() noexcept
{
    try {
        c_plus_plus_function();
    }
    catch (...) {
        // ... local cleanup, if possible and necessary
        errno = E_CPLFLFCTBLEWIT;
    }
}



// section 13.1.7 : exceptions and efficiency
void f()
{
    string buf;
    cin >> buf;
    // ...
    g(1);
    h(buf);
}


bool g(intl);
bool h(const char*);
char* read_long_string();

bool f()
{
    char* s = read_long_string();
    // ...
    if (g(1)) {
        if (h(s)) {
            free(s);
            return true;
        }
        else {
            free(s);
            return false;
        }
    }
    else {
        free(s);
        return false;
    }
}


void g(int) noexcept;
void h(const string&) noexcept;

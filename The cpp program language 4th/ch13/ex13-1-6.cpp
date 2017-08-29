/**************************************************************
* Name     :  ex13-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月23日
**************************************************************/



/*
example 13.3 : resource management
*/


// naive code
void use_file(const char* fn)
{
    FILE* f = fopen(fn, "r");
    // ... use f ...
    fclose(f);
}


// clumsy code
void use_file(const char* fn)
{
    FILE* f = fopen(fn, "r");
    try {
        // use f ...
    }
    catch (...) {
        // catch every possible exception
        fclose(f);
        throw ;
    }
    fclose(f);
}


void acquire()
{
    // acquire resource 1
    // ...

    // ... use resources ...

    // release resource n
    // ...
    // release resource 1
}


class File_ptr {
    FILE* p;
public :
    // open file n in mode a
    File_ptr(const char* n, const char* a) : p {fopen(n, a)} {
        if (p == nullptr) {
            throw runtime_error {"File_ptr : Can't open file"};
        }
    }

    // open file n in mode a
    File_ptr(const string& n, const char* a) : File_ptr {n.c_str(), a} { }

    // assume ownership of pp
    explicit File_ptr(File* pp) : p {pp} {
        if (p == nullptr) {
            throw runtime_error {"File_ptr : nullptr"};
        }
    }

    // ... suitable move and copy operation ...

    ~File_ptr() { fclose(p); }

    operator File*() { return p; }
};


// good
void use_file(const char* fn)
{
    File_ptr f(fn, "r");
    // ... use f ...
}


class Locked_file_handle {
    File_ptr p;
    unique_lock<mutex> lck;
public :
    X(const char* file, mutex& m)
        // acquire "file"
        : p {file, "rw"},
        // acquire "m"
        lck {m}
    { }
    // ...
};



// section 13.3.1 : finally
// ad hoc
template<typename F>
struct Final_action {
    Final_action(F f) : clean {f} { }
    ~Final_action() { clean(); }
    F clean;
};

template<class F>
Final_action<F> finally(F f)
{
    return Final_action<F>(f);
}

// handle undiciplined resource acquisition
// demonstrate that arbitrary actions are possible
void test()
{
    // probably should use a unique_ptr
    int* p = new int{7};
    // C-style allocation
    int* buf = (int*) malloc(10 * sizeof(int));
    auto act1 = finally(
        [&] {
            delete p;
            // C-style deallocation
            free(buf);
            cout << "Goodby, Cruel world!\n";
        }
    );

    int var = 0;
    cout << "var = " << var << '\n';
    // nested block
    {
        var = 1;
        auto act2 = finally([&] {
            cout << "finally!\n";
            var = 7;
            }
        );
        cout << "var = " << var << '\n';
    }   // act2 is invoked here
    cout << "var = " << var << '\n';
}   // act1 is invoked here


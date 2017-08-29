/**************************************************************
* Name     :  ex5-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/



/*
example 5.3 :concurrency
    5.3.1 : tasks and threads

threads of a program share a single address space. in this, threads differ from processes, which
generally do not directly share data.
*/


#include <iostream>
#include <thread>

using namespace std;




// function
void f();

// function object
struct F {
    // F's call operator
    void operator()();
};

//
void user()
{
    // executes in separate thread
    thread t1 {f};
    // executes in separate thread
    thread t2 {F()};
    // wait for t1, the join() ensures that we don't exit user() until the thread have completed.
    t1.join();
    // wait for t2
    t2.join();
}


// implementation of f()
void f()
{
    cout << "Hello ";
}


//
void F::operator()()
{
    cout << "Parallel World!\n";
}



// main test block
int main()
{
    // error : unpredictable output and vary between different executions of the program.
    user();

    return 0;
}

/**************************************************************
* Name     :  ex41-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月23日
**************************************************************/



/*
example 41.1: introduction
example 41.2: memory model
*/


// add  1 to x:
load x into cache element Cx
load Cx into register Rx
Rx = Rx + 1
store Rx back into Cx
store Cx back into x


// section 41.2.1: memory location
// thread 1:
// thread 2:
char c = 0;
char b = 0;
void f();
void g()
{
    {
        c = 1;
        b = 1;
        int x = c;
        int y = b;
    }
}

struct S {
    // location #1
    char a;
    // location #2
    int b : 5;
    unsigned c : 11;
    // note: 0 is "special"
    unsigned : 0;
    // location #3
    unsigned d : 8;
    // location #4
    struct {
        int ee:8;
    } e;
};


// section 41.2.2: instruction reordering
// thread 1:
int x;
bool x_init;
void init()
{
    // no use of x_init in initialize()
    x = initialize();
    //
    x_init = true;
}

// thread 2:
extern int x;
extern bool x_init;

void f2()
{
    int y;
    while (!x_init) {
        // if necessary, wait for initialization to complete
        this_thread::sleep_for(milliseconds{10});
    }
    y = x;
    // ...
}


// section 41.2.3: memory order
// section 41.2.4: data races

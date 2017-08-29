/**************************************************************
* Name     :  ex15-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月31日
**************************************************************/



/*
example 15.4 : programs
*/


int main()
{
    // ...
}

int main(int argc, char* argv[])
{
    // ...
}


// section 15.4.1 : initialization of nonlocal variables
// nonlocal variables
double x = 2;
double y;
double sqx = sqrt(x + y);

// a good alternative to a global variable
int& use_count()
{
    static int uc = 0;
    return uc;
}

void f9)
{
    // read and increment
    cout << ++use_count();
    // ...
}



// section 15.4.2 : initialization and concurrency


// section 15.4.3 : program termination
// standard library atexit()
void my_cleanup();

void somewhere()
{
    if (atexit(&my_cleanup) == 0) {
        // my_cleanup will be called at normal termination
    }
    else {
        // oops : too many atexit functions
    }
}


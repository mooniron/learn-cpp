/**************************************************************
* Name     :  ex13-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月23日
**************************************************************/



/*
example 13.1 : error handling
    section 13.1.1 : exceptions
*/


void taskmaster()
{
    try {
        auto result = do_task();
        // use result
    }
    catch (some_error) {
        // failure to do_task : handle problem
    }
}

int do_task()
{
    // ...
    if (/* would perform the task */) {
        return result;
    }
    else {
        throw some_error{};
    }
}


struct Range_error {};

void f(int n)
{
    if (n < 0 || max < n) {
        throw Range_error {};
    }
    // ...
}


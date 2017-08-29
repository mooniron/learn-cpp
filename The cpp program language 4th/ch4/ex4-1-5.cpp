/**************************************************************
* Name     :  ex4-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月18日
**************************************************************/


/*
example 4.3 : stream I/O
    4.3.2 : input
*/

#include <iostream>
#include <string>

using namespace std;


void f()
{
    int i;
    // read an integer into i
    cin >> i;
    double d;
    // read d double-precision floating-point number into d
    cin >> d;
}

void hello()
{
    cout << "Please enter your name\n";
    string str;
    cin >> str;
    cout << "Hello, " << str << "!\n";
}


// get a line
void hello_line()
{
    cout << "Please enter your name\n";
    string str;
    getline(cin, str);
    cout << "Hello, " << str << "!\n";
}



int main()
{
    //hello();
    hello_line();

    return 0;
}

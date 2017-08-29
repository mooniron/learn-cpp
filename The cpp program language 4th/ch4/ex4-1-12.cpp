/**************************************************************
* Name     :  ex4-1-12.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月19日
**************************************************************/


/*
example 4.5 : algorithms
    4.5.3 : stream iterators

istream_iterator : input iterators are used in pairs representing a sequence.
ostream_iterator : mimic writing into an array through a pointer.
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
// for ostream_iterator and istream_iterator
#include <iterator>
#include <algorithm>

using namespace std;


// write strings to cout
ostream_iterator<string> oo {cout};

//
//istream_iterator<string> ii {cin};
// default end of input istream_iterator
//istream_iterator<string> eos {};

int stream_iterator_test();

// main test function
int main()
{
    // meaning cout << "Hello, "
    *oo = "Hello, ";
    ++oo;
    // meaning cout << "world!\n"
    *oo = "world!\n";

    // all works fine
    if (stream_iterator_test() == 0)
    {
        *oo = "successfully!\n";
    }
    else
    {
        *oo = "error!\n";
    }   // end if

    return 0;
}   // end function main


// read a file, sort the words read, eliminate duplicates, and write the result to another file
int stream_iterator_test()
{
    string from, to;
    // get source and target file names
    cin >> from >> to;
    //cout << from << "\n" << to << endl;

    // input stream for file 'from"
    ifstream is {from};
    // input iterator for stream
    istream_iterator<string> ii {is};
    // input sentinel
    istream_iterator<string> eos {};

    // output stream for file "to"
    ofstream os {to};
    // output stream iterator, "\n" is to delimit output values
    ostream_iterator<string> oo {os, "\n"};

    // b is a vector initiallized from input [ii : eos)
    //vector<string> b {ii, eos};
    // sort the buffer
    //sort(b.begin(), b.end());
    // copy buffer to output, discard replicated values
    //unique_copy(b.begin(), b.end(), oo);

    // a set version : more elegant than vector version
    // collect strings from input
    set<string> b {ii, eos};
    // copy buffer to output
    copy(b.begin(), b.end(), oo);

    // return error state
    return !is.eof() || !os;
}   // end function stream_iterator_test

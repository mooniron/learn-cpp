/**************************************************************
* Name     :  ex8-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月2日
**************************************************************/


/*
example 8.2 : structures
    8.2.3 : structures and classes
*/


#include <iostream>

using namespace std;


struct Point {
    int x, y;
};

struct Points {
    // must contain at least 1 point
    vector<Point> elem;
    Points(Point p0) { elem.push_back(p0); }
    //
    Points(Point p0, Point p1) { elem.push_back(p0); elem.push_back(p1); }
    // ...
};


// error : no default constructor
Points x0;
// one point
Points x1 {{100, 200}};
// two points
Points x2 {{100, 200}, {300, 400}};


// danger : uninitialize in local scope
Point p0;
//  default dconstruction : {{}, {}}; that is {0, 0}
Point p1 {};
// the second member is default constructed : {{1}, {}}; that is {1, 0}
Point p2 {1};
// {1, 2}
Point p3 {1, 2};


struct Address {
    // "Jim Dandy"
    string name;
    // 61
    int number;
    // "South Street"
    string street;
    // "New Providence"
    string town;
    // 'N' 'J'
    char state[2];
    // 07974
    char zip[5];
    //
    Address(const string& n, int nu, const string& s,, const string& t, const string& st, int z);
};


// Address constructor definition
Address::Address(const string& n, int nu, const string& s, const string& t, const string& st, int z)
    // validate postal code
    : name {n}, number {nu}, street {s}, town {t}
{
    if (st.size() != 2) {
        error("State abbreviation should be two characters");
    }   // end if
    // store postal code as characters
    state = {st[0], st[1]};
    // an output string stream
    ostringstream ost;
    // extract characters from int
    ost << z;
    string zi {ost.str()};
    switch (zi.size()) {
        case 5 :
            zip = {zi[0], zi[1], zi[2], zi[3], zi[4]};
            break;
        // starts with '0'
        case 4 :
            zip = {'0', zi[0], zi[1], zi[2], zi[3]};
            break;
        default :
            // cerr and exit
            error("unexpected ZIP code format");
            //break;
    }   // end switch

    // ... check that the code makes sense ...
}


Address jd = {
    "Jim Dandy",
    61,
    "South St",
    "New Providence",
    "NJ",
    // (07974 would be octal)
    7974
};

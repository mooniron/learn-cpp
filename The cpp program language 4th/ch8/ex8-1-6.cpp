/**************************************************************
* Name     :  ex8-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月3日
**************************************************************/


/*
example 8.2 : structures
    8.2.4 : structures and arrays
*/


#include <iostream>

using namespace std;


struct Point {
    int x, y
};

Point points[3] {{1, 2}, {3, 4}, {5, 6}};
int x2 = points[2].x;

struct Array {
    Point elem[3];
};

Array points2 {{1, 2}, {3, 4}, {5, 6}};
int y2 = points2.elem[2].y;


Array shift(Araay a, Point p)
{
    for (int i = 0; i != 3; ++i) {
        a.elem[i].x += p.x;
        a.elem[i].y += p.y;
    }   // end for

    return a;
}   // end function shift

Array ax = shift(points2, {10, 20});


// a simple std array
template<typename T, size_t N>
// simplified
struct array {
    T elem[N];
    T* begin() noexcept { return elem; }
    const T* begin() const noexcept { return elem; }
    T* end() noexcept { return elem + N; }
    const T* end() const noexcept { return elem + N; }
    constexpr size_t size() noexcept;
    T& operator[](size_t n) { return elem[n]; }
    const T& operator[](size_t n) const { return elem[n]; }
    T* data() noexcept { return elem; }
    const T* data() const noexcept { return elem; }
    // ...
};


// std::array version
struct Point {
    int x, y
};

// array of 3 Points
using Array = array<Point, 3>;

Array points {{1, 2}, {3, 4}, {5, 6}};
int x2 = points[2].x;
int y2 = points[2].y;

Array shift(Array a, Point p)
{
    for (int i = 0; i != a.size(); ++i) {
        a[i].x += p.x;
        a[i].y += p.y;
    }   // end for
    return a;
}   // end function shift

Array ax = shift(points, {10, 20});



//
ostream& operator<<(ostream& os, Point p)
{
    //cout << '{' << p[i].x << ',' << p[i].y << '}';
    cout << '{' << p.x << ',' << p.y << '}';
}


// must specify number of elements
void print(Point a[], int s)
{
    for (int i = 0; i != s; ++i) {
        cout << a[i] << '\n';
    }
}   // end function print


template<typename T, int N>
void print(array<T, N>& a)
{
    for (int i = 0; i != a.size(); ++i) {
        cout << a[i] << '\n';
    }   // end for
}


// 3 elements
Point point1[] = {{1, 2}, {3, 4}, {5, 6}};
// 3 elements
array<Point, 3> point2 = {{1, 2}, {3, 4}, {5, 6}};

void ftest()
{
    // 4 is a bad error
    print(point1, 4);
    //
    print(point2);
}


// 3 elements
Point point1[] = {{1, 2}, {3, 4}, {5, 6}};
// 3 elements
array<Point, 3> point2 = {{1, 2}, {3, 4}, {5, 6}};
// error : number of elements not given
array<Point> point3 = {{1, 2}, {3, 4}, {5, 6}};

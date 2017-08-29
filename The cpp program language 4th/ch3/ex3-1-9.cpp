/**************************************************************
* Name     :  ex3-1-9.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.3 : copy and move
    3.3.4 : suppressing operations
    elemenate the move and copy operation for a hierarchic class
delete : it can be used to suppress any operation.
*/

class Shape {
public :
    // no copy operations
    Shape(const Shape&) = delete;
    Shape& operator=(const Shape&) = delete;

    // no move operations
    Shape(Shape&&) = delete;
    Shape& operator=(Shape&&) = delete;

    ~Shape();
    // ...
};


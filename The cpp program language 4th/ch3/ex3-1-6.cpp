/**************************************************************
* Name     :  ex3-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.2.4 : class hira
*/


#include <iostream>

using namespace std;

class Shape {
public :
    // pure virtual
    virtual point center() const = 0;
    virtual void move(point to) = 0;

    // draw on current "canvas"
    virtual void draw() const = 0;
    virtual void rotate(int angle) = 0;

    // destructor
    virtual ~Shape() {}
    // ...
    };  // end class Shape


/*  vectors of pointers to shape  */
// rotate v's elements by angle degrees
void rotate_all(vector<Shape>& v, int angle) {
    for (auto p : v) {
        p->rotate(angle);
        }   // end for
    }   // end function rotate_all


/*  Circle class  : derived from public Shape  */
class Circle : public Shape {

public :
    // constructor
    Circle(point p, int rr);
    //
    point center() const { return x; }
    //
    void move(point to) { x = to; }

    //
    void draw() const;
    // nice simple algorithm
    void rotate(int) {}

private :
    // center point
    point x;
    // radius
    int r;
    //
    };  // end class Circle


/*  class Smiley : use Circle as the basis for a face  */
class Smiley : public Circle {
public :
    // constructor
    Smiley(point p, int r) : Circle {p, r}, mouth {nullptr} {}
    // destructor
    ~Smiley() {
        delete mouth;
        for (auto p : eyes) {
            delete p;
            }
        }   // end destructor
    //
    void move(point to);
    //
    void draw() const;
    //
    void rotate(int);
    void add_eye(Shape* s) { eyes.push_back(s); }
    void set_mouth(Shape* s);
    // wink eye number i
    virtual void wink(int i);
    // ...
private :
    // usually two eyes
    vector<Shape*> eyes;
    Shape* mouth;
    };  // end class Smiley


/*  definition Smilly::draw()  */
void Smiley::draw() {
    Circle::draw();
    for (auto p : eyes) {
        p->draw();
        }   // end for
    mouth->draw();
    }   // end function Smiley::draw


/*  class hierarchy  */
enum class Kind { circle, triangle, smiley };
// read_shape description from is istream
Shape* read_shape(istream& is) {
    // ... read_shape header from is and find its kind k ...
    switch(k) {
        case kind::circle :
            // read circle data { point, int } into p and r
            return new Circle {p, r};
        case kind::triangle :
            // read triangle data { point, point, point } into p1, p2, p3
            return new Triangle {p1, p2, p3};
        case kind::smiley :
            // read smiley data { point, int, Shape*, Shape*, Shape* } into p, r, e1, e2, and m
            Smiley* ps = new Smiley {p, r};
            ps->add_eye(e1);
            ps->add_eye(e2);
            ps->set_mouth(m);
            return ps;
        //
        }   // end switch
    }   // end function read_shape


/*  use the shape  */
void use() {
    std::vector<Shape*> v;
    //
    while (cin) {
        v.push_back(read_shape(cin));
        }   // end while
    // call draw() for each element
    draw_all(v);
    // call rotate(45) for each element
    rotate_all(v, 45);
    // remember to delete members
    for (auto p : v) {
        delete p;
        }   // end for
    }   // end function user



/*  Experienced programmers will notice that I left open two obvious opportunities for mistakes:
• A user might fail to the pointer returned by shape().
• The owner of a container of Shape pointers might not delete the objects pointed to.
*/

/*  unique_ptr  */
// read_shape description from is istream
//Shape* read_shape(istream& is) {
unique_ptr<Shape> read_shape_better(istream& is) {
    // ... read_shape header from is and find its kind k ...
    switch(k) {
        case kind::circle :
            // read circle data { point, int } into p and r
            return unique_ptr<Shape> { new Circle {p, r} };
        case kind::triangle :
            // read triangle data { point, point, point } into p1, p2, p3
            return unique_ptr<Shape> { new Triangle {p1, p2, p3} };
        case kind::smiley :
            // read smiley data { point, int, Shape*, Shape*, Shape* } into p, r, e1, e2, and m
            unique_ptr<Smiley> ps = unique_ptr<Shape> { new Smiley {p, r} };
            ps->add_eye(e1);
            ps->add_eye(e2);
            ps->set_mouth(m);
            return ps;
        //
        }   // end switch
    }   // end function read_shape_better

/*
    unique_ptr will delete its objects if unique_ptr goes out of scope
*/
void user_better() {
    vector<unique_ptr<Shape>> v;
    while (cin) {
        //
        v.push_back(read_shape_better(cin));
        }   // end while
    // call draw() for each element
    draw_all(v);
    // call rotate(45) for each element
    rotate_all(v, 45);
    //
    }   // all shapes implicitly destroyed,  // end function user_better


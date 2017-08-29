/**************************************************************
* Name     :  ex20-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月2日
**************************************************************/



/*
example 20.4 : abstract classes
*/


class Shape {
public :
    // inelegant
    virtual void rotate(int)
    {
        throw runtime_error {"Shape::rotate"};
    }
    virtual void draw() const
    {
        throw runtime_error {"Shape::draw"};
    }
    // ...
};


// abstract class
class Shape {
public :
    // pure virtual function
    virtual void rotate(int) = 0;
    // pure virtual function
    virtual void draw() const = 0;
    // pure virtual function
    virtual bool is_closed() const = 0;
    // ...
    // virtual destructor
    virtual ~Shape();
};

// error : variable of abstract class shape
Shape s;

// derived classes
class Point { /* ... */ };

class Circle : public Shape {
public :
    void rotate(int) override { }
    void draw() const override;
    bool is_closed() const override { return true; }
    Circle(Point p, int r);
private :
    Point center;
    int radius;
};

// abstract class
class Polygon : public Shape {
public :
    bool is_closed() const override
    {
        return true;
    }
    // ... draw and rotate not overridden ...
};

// error : declaration of object of abstract class Polygon
Polygon b {p1, p2, p3, p4};

class Erregular_polygon : public Polygon {
    list<Point> lp;
public :
    Irregular_polygon(initializer_list<Point>);
    void draw() const override;
    void rotate(int) override;
    // ...
};

// assume that p1 .. p4 are Points defined somewhere
Irregular_polygon poly {p1, p2, p3, p4};


class Character_device {
public :
    virtual int open(int opt) = 0;
    virtual int close(int opt) = 0;
    virtual int read(char* p, int n) = 0;
    virtual int write(const char* p, int n) = 0;
    // device I/O control
    virtual int ioctl(int ...) = 0;
    // virtual destructor
    virtual ~Character_device() { }
};

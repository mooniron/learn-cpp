/**************************************************************
* Name     :  ex22-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月9日
**************************************************************/



/*
example 22.3 : double dispatch and visitors
*/


// section 22.3.1 : double dispatch
void do_something(Shape& s1, Shape&  s2)
{
    if (s1.intersect(s2)) {
        // the two shapes overlap
    }
    // ...
}


class Circle;
class Triangle;

class Shape {
public :
    virtual bool intersect(const Shape&) const = 0;
    virtual bool intersect(const Circle&) const = 0;
    virtual bool intersect(const Triangle&) const = 0;
};

class Circle : public Shape {
public :
    bool intersect(const Shape&) const override;
    virtual bool intersect(const Circle&) const override;
    virtual bool intersect(const Triangle&) const override;
};

class Triangle : public Shape {
public :
    bool intersect(const Shape&) const override;
    virtual bool intersect(const Circle&) const override;
    virtual bool intersect(const Triangle&) const override;
};


bool Circle::intersect(const Shape& s) const
{
    return s.intersect(*this);
}

bool Circle::intersect(const Circle&) const
{
    cout << "intersect(circle, circle)\n";
    return true;
}

bool Circle::intersect(const Triangle&) const
{
    cout << "intersect(circle, triangle)\n";
    return true;
}

bool Triangle::intersect(const Shape& s) const
{
    return s.intersect(*this);
}

bool Triangle::intersect(const Circle&) const
{
    cout << "intersect(triangle, circle)\n";
    return true;
}

bool Triangle::intersect(const Triangle&) const
{
    cout << "intersect(triangle, triangle)\n";
    return true;
}


void test(Triangle& t, Circle& c)
{
    vector<pair<Shape*, Shape*>> vs {
        {&t, &t},
        {&t, &c},
        {&c, &t},
        {&c, &c}
    };

    for(auto p : vs) {
        p.first->intersect(*p.second);
    }
}


class Shape {
public :
    // the rect angle encloses the shape
    virtual Rectangle box() const = 0;
    // ...
};

class Circle : public Shape {
public :
    Rectangle box() const override;
    // ...
};

class Triangle : public Shape {
public :
    Rectangle box() const override;
    // ...
};

// simple to calculate
bool intersect(const Rectangle&, const Rectangle&);

bool intersect(const Shape&, const Shape&)
{
    return intersect(s1.box(), s2.box())
}

bool intersect(const Shape& s1, const Shape& s2)
{
    auto i = index(type_id(s1), type_id(s2));
    return intersect_tbl[i](s1, s2);
}


// section 22.3.2 : visitors
class Visitor;

class Node {
public :
    virtual void accept(Visitor&) = 0;
};

class Expr : public Node {
public :
    void accept(Visitor&) override;
};

class Stmt : public Node {
public :
    void accept(Visitor&) override;
};


void Expr::accept(Visitor& v)
{
    v.accept(*this);
}

void Stmt::accept(Visitor& v)
{
    v.accept(*this);
}


class Visitor {
public :
    virtual void accept(Expr&) = 0;
    virtual void accept(Stmt&) = 0;
};


class Do1_visitor : public Visitor {
public :
    void accept(Expr&) { cout << "do1 to Expr\n"; }
    void accept(Stmt&) { cout << "do1 to Stmt\n"; }
};

class Do2_visitor : public Visitor {
public :
    void accept(Expr&) { cout << "do2 to Expr\n"; }
    void accept(Stmt&) { cout << "do2 to Stmt\n"; }
};


void test(Expr& e, Stmt& s)
{
    vector<pair<Node*, Visitor*>> vn {
        {&e, &do1};
        {&s, &do1};
        {&e, &do2};
        {&s, &do2};
    };
    for (auto p : vn) {
        p.first->accept(*p.second);
    }
}



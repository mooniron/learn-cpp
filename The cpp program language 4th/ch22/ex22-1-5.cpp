/**************************************************************
* Name     :  ex22-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月9日
**************************************************************/



/*
example 22.6 : uses and misuses of RTTI
*/


// misuse of run-time type information RTTI

void rotate(const Shape& r)
{
    if (typeid(r) == typeid(Circle)) {
        // do nothing
    }
    else if (typeid(r) == typeid(Triangle)) {
        // ... rotate triangle ...
    }
    else if (typeid(r) == typeid(Square)) {
        // ... rotate square ...
    }
    // ...
}


// misuse of run-time type information
// polymorphic
class Object {
    // ...
};

class Container : public Object {
public :
    void put(Object*);
    Object* get();
    // ...
};
class Ship : public Object { /* ... */ };

Ship* f(Ship* ps, Container* c)
{
    // put the Ship into the container
    c->put(ps);
    // retrieve an Object from the container
    Object* p = c->get();
    // run-time check that the Object  is a Ship
    if (Ship* q = dynamic_cast<Ship*>(p)) {
        return q;
    }
    else {
        // ... do something else (typically, error handling) ...
    }
}


Ship* f2(Ship* ps, vector<Ship*>& c)
{
    // put the Ship into the container
    c.push_back(ps);
    // ...
    // retrieve a Ship from the container
    return c.pop_back();
}


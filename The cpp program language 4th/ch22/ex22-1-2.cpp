/**************************************************************
* Name     :  ex22-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月9日
**************************************************************/



/*
example 22.2 : class hierarchy navigation
*/


void my_event_handler(BBwindow* pw)
{
    // does pw point to an Ival_box?
    if (auto pb = dynamic_cast<Ival_box*>(pb)) {
        // ...
        // use the Ival_box
        int x = pb->get_value();
    }
    else {
        // ... oops! cope with unexpected event ...
    }
}


// section 22.2.1 : dynamic_cast
class BB_ival_slider : public Ival_slider, protected BBslider {
    // ...
};

void f(BB_ival_slider* p)
{
    // ok
    Ival_slider* pi1 = p;
    // ok
    Ival_slider* pi2 = dynamic_cast<Ival_slider*>(p);
    // error : BBslider is a protected base
    BBslider* pbb1 = p;
    // ok : pbb2 becomes nullptr
    BBslider* pbb2 = dynamic_cast<BBslider*>(p);
}

// polymorphic base (Ival_slider has virtual functions)
class My_slider : public Ival_slider {
    // ...
};

// base not polymorphic (Date has no virtual functions)
class My_date : public Date {
    // ...
};

void g(Ival_box* pb, Date* pd)
{
    // ok
    My_slider* pd1 = dynamic_cast<My_slider*>(pb);
    // error : Date not polymorphic
    My_date* pd2 = dynamic_cast<My_date*>(pd);
}

// base class for object I/O system
class Io_obj {
    virtual Io_obj* clone() = 0;
};

class Io_date : public Date, public Io_obj {
};

void f(Io_obj* pio)
{
    Date* pd = dynamic_cast<Date*>(pio);
    // ...
}

void g(Ival_box* pb, Date* pd)
{
    // ok
    void* pb2 = dynamic_cast<void*>(pb);
    // error : Date not polymorphic
    void* pd2 = dynamic_cast<void*>(pd);
}


// section 22.2.1.1 : dynamic_cast to reference
void fp(Ival_box* p)
{
    // does p point to an Ival_slider ?
    if (Ival_slider* is = dynamic_cast<Ival_slider*>(p)) {
        // ... use is ...
    }
    else {
        // ... *p not a slider; handle alternatives
    }
}

void fr(Ival_box& r)
{
    // r references an Ival_slider! otherwise throw bad_cast exception
    Ival_slider& is = dynamic_cast<Ival_slider&>(r);
    // ... use is ...
}


void g(BB_ival_slider& slider, BB_ival_dial& dial)
{
    try {
        // pointer to BB_ival_slider passed as Ival_box*
        fp(&slider);
        // reference to BB_ival_slider passed as Ival_box&
        fr(slider);
        // pointer to BB_ival_dial passed as Ival_box*
        fp(&dial);
        // dial passed as Ival_box
        fr(dial);
    }
    catch (bad_cast) {
        // section 30.4.1.1
        // ...
    }
}


// section 22.2.2 : multiple inheritance
class Component : public virtual Storable { /* ... */ };
class Receiver : public Component { /* ... */ };
class Transmitter : public Component { /* ... */ };
class Radio : public Receiver, public Transmitter { /* ... */ };

void h1(Radio& r)
{
    // a Radio has a unique Storable
    Storable* ps = &r;
    // ...
    // pc = 0; a Radio has two Components
    Component* pc = dynamic_cast<Component*>(ps);
    // ...
}

// ps might or might not point to a Component
void h2(Storable* ps)
{
    if (Component* pc = dynamic_cast<Component*>(ps)) {
        // we have a Component!
    }
    else {
        // it wasn't a Component
    }
}


// section 22.2.3 : static_cast and dynamic_cast
void g(Radio& r)
{
    // Receiver is an ordinary base of Radio
    Receiver* prec = &r;
    // ok, unchecked
    Radio* pr = static_cast<Radio*>(prec);
    // ok, run-time checked
    pr = dynamic_cast<Radio*>(prec);
    // Storable is a virtual base of Radio
    Storable* ps = &r;
    // error : cannot cast from virtual base
    pr = static_cast<Radio*>(ps);
    // ok, run-time checked
    pr = dynamic_cast<Radio*>(ps);
}

Radio* f1(void* p)
{
    // trust the programmer
    Storable* ps = static_cast<Storable*>(p);
    return dynamic_cast<Radio*>(ps);
}


class Users : private set<Person> { /* ... */ };
void f2(Users* pu, const Receiver* pcr)
{
    // error : access violation
    atic_cast<set<Person>*>(pu);
    // error : access violation
    dynamic_cast<set<Person>*>(pu);
    // error : can't cast away const
    staic_cast<Receiver*>(pcr);
    // error : can't cast away const
    dynamic_cast<Receiver*>(pcr);
    // ok
    Receiver* pr = const_cast<Receiver*>(pcr);
    // ...
}


// section 22.2.4 recovering an interface
void user()
{
    // ... open file assumed to hold shapes, and attach ss as an istream for that file ...
    // read object from stream
    unique_ptr<Io_obj> p {get_obj(ss)};
    if (auto sp = dynamic_cast<Shape*>(p.get())) {
        // use the Shape
        sp->draw();
        // ...
    }
    else {
        // oops : non-shape in Shape file
    }
}

class Io_obj {
public :
    // polymorphic
    virtual Io_obj* clone() const = 0;
    virtual ~Io_obj() { }
};


// pointer to function returning an Io_obj*
using Pf = Io_obj*(istream&);
// my version
using Pf = Io_obj* (*)(istream&)

// maps strings to creation functions
map<string, Pf> io_map;
// read a word from is throw Read_error if the read failed
string get_word(istream& is);

Io_obj* get_obj(istream& is)
{
    // read initial word
    string str = get_word(is);
    // look up str to get function
    if (auto f = io_map[str]) {
        // call function
        return f(is);
    }
    // no match for str
    throw Unknown_class {};
}

class Shape : public Io_obj {
    // ...
};

struct Io_circle : Circle, Io_obj {
    // initialize from input stream
    Io_circle(istream&);
    // use copy constructor
    Io_circle* clone() const { return new Io_circle {*this}; }
    // for io_map
    static Io_obj* new_circle(istream& is) { return new Io_circle {is}; }
};

io_map["Io_circle"] = &Io_circle::new_circle;

class Io_triangle : public Triangle, public Io_obj { // ...};
// somewhere
io_map["Io_triangle"] = &Io_circle::new_triangle;


template<class T>
struct Io : T, Io_obj {
public :
    // initialize from input stream
    Io(istream&);
    Io* clone() const override { return new Io {*this}; }
    // for io_map
    static Io* new_io(istream& is) { return new Io {is}; }
};

using Io_circle = Io<Circle>;


void f(io<Shape>& ios)
{
    Shape* ps = &ios;
    // ...
}

// wrap concrete type
using Io_date = Io<Date>;
// error : cannot derive from built-in type
using Io_int = Io<int>;


template<class T>
struct Io : Io_obj {
    T val;
    // initialize from input stream
    Io(istream&);
    Io* clone() const override { return new Io {*this}; }
    // for io_map
    static Io_obj* new_io(istream& is) { return new Io {is}; }
};

// wrap built-in type
using Io_int = Io<int>;

template<typename T>
T* get_val<T>(Io_obj* p)
{
    if (auto pp = dynamic_cast<Io<T>*>(p)) {
        return &pp->val;
    }
    return nullptr;
}

void user()
{
    // ... open file assumed to hold shapes, and attach ss as an istream for that file ...
    // read object from stream
    unique_ptr<Io_obj> p {get_obj(ss)};

    if (auto sp = get_val<Shape>(p.get())) {
        // use the Shape
        sp->draw();
        // ...
    }
    else {
        // oops : cope with non-shape in Shape file ...
    }
}


class Face : public Shape {
public :
    Shape* outline;
    array<Shape*> eyes;
    Shape* mouth;
    // ...
};


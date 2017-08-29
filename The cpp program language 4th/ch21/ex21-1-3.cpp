/**************************************************************
* Name     :  ex21-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月2日
**************************************************************/



/*
example 21.3 : multiple inheritance
*/


// section 21.3.1 : multiple interfaces

// section 21.3.2 : multiple implementation classes
class Comm_sat : public Satellite, public Displayed {
public :
    // ...
};

void f(Comm_sat& s)
{
    // Displayed::draw()
    s.draw();
    // Satellite::center()
    Pos p = s.center();
    // Comm_sat::transmit()
    s.transmit();
}

void highlight(Displayed*);
Pos center_of_gravity(const Satellite*);

void g(Comm_sat* p)
{
    // pass a pointer to the Displayed part of the Comm_sat
    highlight(p);
    // pass a pointer to the Satellite part of the Comm_sat
    Pos x = center_of_gravity(p);
}


class Satellite {
public :
    // center of gravity
    virtual Pos center() const = 0;
    // ...
};

class Displayed {
public :
    virtual void draw() = 0;
    // ...
};

class Comm_sat : public Satellite, public Displayed {
public :
    // override Satellite::center()
    Pos center() const override;
    // override Displayed::draw()
    void draw() override;
    // ...
};


// section 21.3.3 : ambiguity resolution
class Satellite {
public :
    virtual Debug_info get_debug();
    // ...
};

class Displayed {
public :
    virtual Debug_info get_debug();
    // ...
};

void f(Comm_sat& cs)
{
    // error : ambiguous
    Debug_info di = cs.get_debug();
    // ok
    di = cs.Satellite::get_debug();
    // ok
    di = cs.Displayed::get_debug();
}


class Comm_sat : public Satellite, public Displayed {
public :
    // override Satellite::get_debug and Displayed::get_debug()
    Debug_info get_debug()
    {
        Debug_info di1 = Satellite::get_debug();
        Debug_info di2 = Displayed::get_debug();
        return merge_info(di1, di2);
    }
    // ...
};

class Telstar : public Comm_sat {
public :
    void draw()
    {
        // finds Displayed::draw
        Comm_sat::draw();
        // ... own stuff ...
    }
    // ...
};


// map SimObj facilities to something easier to use for Satellite simulation
class Satellite : public SimObj {
public :
    // call SimObj::DBinf() and extract information
    virtual Debug_info get_debug();
    // ...
};

// map Widget facilities to something easier to use to display Satellite simulation results
class Displayed : public Widget {
public :
    // read Widget data and compose Debug_info
    virtual Debug_info get_debug();
    // ...
};


class Window {
public :
    // display image
    void draw();
    // ...
};

class Cowboy {
public :
    // pull gun from holster
    void draw();
    // ...
};

class Cowboy_window : public Cowboy, public Window {
    // ...
};

struct WWindow : Window {
    // inherit constructors
    using Window::Window;
    // force derived class to override
    virtual void win_draw() = 0;
    // display image
    void draw() override final
    {
        win_draw();
    }
};

struct CCowboy : Cowboy {
    // inherit constructors
    using Cowboy::Cowboy;
    // force derived class to override
    virtual void cow_draw() = 0;
    // pull gun from holster
    void draw() override final
    {
        cow_draw();
    }
};

class Cowboy_window : public CCowboy, public WWindow {
public :
    void cow_draw() override;
    void win_draw() override;
    // ...
};



// section 21.3.4 : repeated use of a base class
// persistent storage
struct Storable {
    virtual string get_file() = 0;
    virtual void read() = 0;
    virtual void write() = 0;
    virtual ~Storable() { }
};

class Transmitter : public Storable {
public :
    void write() override;
    // ...
};

class Receiver : public Storable {
public :
    void write() override;
    // ...
};

class Radio : public Transmitter, public Receiver {
public :
    string get_file() override;
    void read() override;
    void write() override;
    // ...
};

void Radio::write()
{
    Transmitter::write();
    Receiver::write();
    // ... write radio-specific information ...
}



// section 21.3.5 : virtual base classes
class Storable {
public :
    // store in file named s
    Storable(const string& s);
    virtual void read() = 0;
    virtual void write() = 0;
    virtual ~Storable();
protected :
    string file_name;
    Storable(const Storable&) = delete;
    Storable& operator=(const Storable&) = delete;
};

class Transmitter : public virtual Storable {
public :
    void write() override;
    // ...
};

class Receiver : public virtual Storable {
public :
    void write() override;
    // ...
};

class Radio : public Transmitter, public Receiver {
public :
    void write() override;
    // ...
};



// section 21.3.5.1 : constructing virtual bases
struct V {
    V(int i);
    // ...
};

struct A {
    // default constructor
    A();
    // ...
};

struct B : virtual V, virtual A {
    // default constructor; must initialize base V
    B() : V {1} { /* ... */ };
};

class C : virtual V {
public :
    // must initialize base V
    C(int i) V {i} { /* ... */ };
    // ...
};

//
class D : virtual public B, virtual public C {
    // implicitly gets the virtual base V from B and C
    // implicitly gets virtual base A rom B
public :
    // error : no default constructor for V and C
    D() { /* ... */ };
    // error : no default constructor for V
    D(int i) : C {i} { /* ... */ };
    // ok
    D(int i) : V {i}, C {i} { /* ... */ };
};


// section 21.3.5.2 : calling a virtual class member once only
// basic stuff
class Window {
public :
    virtual void draw();
};

// border stuff
class Window_with_border : public virtual Window {
protected :
    // display the border
    void own_draw();
public :
    void draw() override;
};

// menu stuff
class Window_with_menu : public virtual Window {
protected :
    // display the menu
    void own_draw();
public :
    void draw() override;
};

// clock stuff
class Clock : public Window_with_border, public Window_with_menu {
protected :
    // display the clock face and hands
    void own_draw();
public :
    void draw() override;
};

void Window_with_border::draw()
{
    Window::draw();
    // display the border
    own_draw();
}

void Window_with_menu::draw()
{
    Window::draw();
    // display the menu
    own_draw()
}

void Clock::draw()
{
    Window::draw();
    Window_with_border::own_draw();
    Window_with_menu::own_draw();
    // display the clock face and hands
    own_draw();
}



// section 21.3.6 : replicated vs virtual bases
class BB_ival_slider : public Ival_slider, protected BBslider {
    // implementation of functions required by Ival_slider and BBslider, using facilities from BBslider
};

class BB_ival_slider : public virtual Ival_slider, protected BBslider { /* ... */ };
class Popup_ival_slider : public virtual Ival_slider { /* ... */ };
class BB_popup_ival_slider : public virtual Popup_ival_slider, protected BB_ival_slider { /* ... */ };

class BB_ival_slider : public  Ival_slider, protected BBslider { /* ... */ };
class Popup_ival_slider : public  Ival_slider { /* ... */ };
class BB_popup_ival_slider : public  Popup_ival_slider, protected BB_ival_slider { /* ... */ };


void f(Ival_slider* p);
// replicated version
void g(BB_popup_ival_sliderz* p)
{
    // error : Popup_ival_slider::Ival_slider or BB_ival_slider::Ival_slider ?
    f(p);
}



// section 21.3.6.1 : overriding virtual base functions
class Window {
    // ...
    // set background color
    virtual void set_color(Color) = 0;
    //
    virtual void prompt() = 0;
};

class Window_with_border : public virtual Window {
    // ...
    // control background color
    void set_color(Color) override;
};

class Window_with_menu : public virtual Window {
    // ...
    // control user interactions
    void prompt() override;
};

class My_window : public Window_with_menu, public Window_with_border {
    // ...
    // don't leave user interactions to base
    void prompt() override;
};


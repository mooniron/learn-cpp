/**************************************************************
* Name     :  ex21-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月2日
**************************************************************/



/*
example 21.2 : design of class hierarchies
*/


// section 21.2.1 implementation inheritance
class Ival_box {
protected :
    int val;
    int low, high;
    // changed by user using set_value()
    bool changed {false};
public :
    Ival_box(int ll, int hh) : val {ll}, low {ll}, high {hh} { }

    // for application
    virtual int get_value()
    {
        changed = false;
        return val;
    }

    // for user
    virtual void set_value(int i)
    {
        changed = true;
        val = i;
    }

    // for application
    virtual void reset_value(int i)
    {
        changed = false;
        val = i;
    }
    virtual void prompt() {}
    virtual bool was_changed() const
    {
        return changed;
    }
    virtual ~Ival_box() { };
};


// use Ival_box
void interact(Ival_box* pb)
{
    // alert user
    pb->prompt();
    // ...
    int i = pb->get_value();
    if (pb->was_changed()) {
        // ... new value...
    }
    else {
        // ... do something else ...
    }
}

void some_fct()
{
    // Ival_slider derived from Ival_box
    unique_ptr<Ival_box> p1 {new Ival_slider {0, 5}};
    interact(p1.get());
    unique_ptr<Ival_box> p2 {new Ival_dial {1, 12}};
    interact(p2.get());
}


class Ival_slider : public Ival_box {
private :
    // ... graphics stuff to  define what the slider looks like, etc ...
public :
    Ival_slider(int, int);
    // get value from user and deposit it in val
    int get_value() override;
    void prompt() override;
};


// rewritten to use BBwidget
class Ival_box : public BBwidget { /* ... */ };
class Ival_slider : public Ival_box { /* ... */ };
class Ival_dial : public Ival_box { /* ... */ };
class Flashing_ival_slider : public Ival_slider { /* ... */ };
class Popup_ival_slider : public Ival_slider { /* ... */ };


// section 21.2.1.1 : critique
class Ival_box : public BBwidget { /* ... */ };
class Ival_box : public CWwidget { /* ... */ };
class Ival_box : public IWwidget { /* ... */ };
class Ival_box : public LSwindow { /* ... */ };


// section 21.2.2 : interface inheritance
class Ival_box {
public :
    virtual int get_value() = 0;
    virtual void set_value(int i) = 0;
    virtual void reset_value(int i) = 0;
    virtual void prompt() = 0;
    virtual bool was_changed() = 0;
    virtual ~Ival_box() { }
};


class Ival_slider : public Ival_box, protected BBwidget {
public :
    Ival_slider(int, int);
    ~Ival_slider() override;
    int get_value() override;
    void set_value(int i) override;
    // ...
protected :
    // ... functions overriding BBwidget the virtual functions ...
    // e.g., BBwidget::draw(), BBwidget::mouse1hit() ...
private :
    // ... data needed for slider ...
};


void f(Ival_box* p)
{
    // ...
    delete p;
}

// class hierarchy
class Ival_box { /* ... */ };
class Ival_slider : public Ival_box, protected BBwidget { /* ... */ };
class Ival_dial : public Ival_box, protected BBwidget { /* ... */ };
class Flashing_ival_slider : public Ival_slider { /* ... */ };
class Popup_ival_slider : public Ival_slider { /* ... */ };



// section 21.2.3 : alternative implementations
// common
class Ival_box { /* ... */ };
// for BB class
class Ival_slider : public Ival_box, protected BBwidget { /* ... */ };
// for CW
class Ival_slider : public Ival_box, protected CWwidget { /* ... */ };
// ...

// common
class Ival_box { /* ... */ };
// for BB class
class BB_ival_slider : public Ival_box, protected BBwidget { /* ... */ };
// for CW
class CW_ival_slider : public Ival_box, protected CWwidget { /* ... */ };
// ...

// common
class Ival_box { /* ... */ };
// abstract class
class Ival_slider : public Ival_box { /* ... */ };
// for BB class
class BB_ival_slider : public Ival_slider, protected BBwidget { /* ... */ };
// for CW
class CW_ival_slider : public Ival_slider, protected CWwidget { /* ... */ };

// for BB class
class BB_ival_slider : public Ival_slider, protected BBslider { /* ... */ };
// for CW
class CW_ival_slider : public Ival_slider, protected CWslider { /* ... */ };


// rewritten to use BBwidget
class Ival_box : public BBwidget { /* ... */ };
class Ival_slider : public Ival_box { /* ... */ };
class Ival_dial : public Ival_box { /* ... */ };
class Flashing_ival_slider : public Ival_slider { /* ... */ };
class Popup_ival_slider : public Ival_slider { /* ... */ };
// for BB class
class BB_ival_slider : public Ival_slider, protected BBslider { /* ... */ };
class BB_flashing_ival_slider : public Flashing_ival_slider, protected BBwidget_with_bells_and_whistles { /* ... */ };
class BB_popup_ival_slider : public Popup_ival_slider, protected BBslider { /* ... */ };
// for CW
class CW_ival_slider : public Ival_slider, protected CWslider { /* ... */ };
// ...


// section 21.2.3.1 : critique


// section 21.2.4 : localizing object creation
class Ival_maker {
public :
    // make dial
    virtual Ival_dial* dial(int, int) = 0;
    // make popup slider
    virtual Popup_ival_slider* popup_slider(int, int) = 0;
    // ...
};

// make BB versions
class BB_maker : public Ival_maker {
public :
    Ival_dial* dial(int, int) override;
    Popup_ival_slider* popup_slider(int, int) override;
    // ...
};

// make LS versions
class LS_maker : public Ival_maker {
public :
    Ival_dial* dial(int, int) override;
    Popup_ival_slider* popup_slider(int, int) override;
    // ...
};

Ival_dial* BB_maker::dial(int a, int b)
{
    return new BB_ival_dial(a, b);
}

Ival_dial* LS_maker::dial(int a, int b)
{
    return new LS_ival_dial(a, b);
}


void user(Ival_maker& im)
{
    // create appropriate dial
    unique_ptr<Ival_box> pb {im.dial(0, 99)};
    // ...
}

// for BB users
BB_maker BB_impl;
LS_maker LS_impl;

void driver()
{
    // use BB
    user(BB_impl);
    // use LS
    user(LS_impl);
}


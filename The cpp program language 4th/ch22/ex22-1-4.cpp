/**************************************************************
* Name     :  ex22-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月9日
**************************************************************/



/*
example 22.4 : construction and destruction
example 22.5 : type identification
*/


class type_info;
// pseudo declaration
const type_info& typeid(expression);


void f(Shape& r, Shape* p)
{
    // type of the object referred to by r
    typeid(r);
    // type of the object pointed to by p
    typeid(*p);
    // type of the pointer, that is Shape* (uncommon, except as a mistake)
    typeid(p);
}


// polymorphic base class
struct Poly {
    virtual void f();
    // ...
};

// no virtual functions
struct Non_poly { //* ... * };

structt D1 : Poly { //* ... * };
struct D2 : Non_poly { //* ... * };

void f(Non_poly& npr, Poly& pr)
{
    // writes something like "Non_poly"
    cout << typeid(npr).name() << '\n';
    // name of Poly or a class derived from Poly
    cout << typeid(pr).name() << '\n';
}

void g()
{
    D1 d1;
    D2 d2;
    // writes "Non_poly D1"
    f(d2, d1);
    // oops!
    f(*static_cast<Non_poly*>(nullptr), *static_cast<Poly*>(nullptr));
}


class type_info {
    // date
public :
    // is polymorphic
    virtual ~type_info();
    // can be compared
    bool operator==(const type_ifo&) const noexcept;
    bool operator!=(const type_info&) const noexcept;
    // ordering
    bool before(const type_info&) const noexcept;
    // for use by unordered_map
    size_t hash_code() const noexcept;
    // name of type
    const char* name() const noexcept;
    // prevent copying
    type_info(const type_info&) = delete;
    // prevent copying
    type_info& operator=(const type_info&) = delete;
};


#include<typeinfo>

void g(Component* p)
{
    cout << typeid(*p).name();
}


// section 22.5.1 : extended type information
#include <typeinfo>

map<string, Layout> layout_table;

void f(B* p)
{
    // find the Layout based on *p's name
    Layout& x = layout_table[typeid(*p).name()]
    // ... use x ...
}

unordered_map<type_index, Icon> icon_table;

void g(B* p)
{
    // ... use i ...
    Icon& i = icon_table[type_index{typeid(*p)}];
}


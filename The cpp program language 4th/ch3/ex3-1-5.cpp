/**************************************************************
* Name     :  ex3-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 3.2.2 : abstract types class
*/


// abstract Container class
class Container {
public :
    // pure virtual function
    virtual double& operator[](int) = 0;
    // const member function
    virtual int size() const = 0;
    // destructor
    virtual ~Container() {}
};


//
void use(Container& c)
{
    const int sz = c.size();

    for (int i = 0; i != sz; ++i) {
        cout << c[i] << '\n';
        }   // end for
}   // end function use


// function implementation by using concrete class Vector, Vector_Container implements Container
class Vector_Container : public Container {
    Vector v;
public :
    // Vector of s elements
    Vector_Container(int s) : v(s) {}
    // destructor
    ~Vector_Container() {}
    // operator[]
    double& operator[](int i) { return v[i]; }
    //
    int size() const { return v.size(); }
};


// use container
void g()
{
    Vector_Container vc {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    use(vc);
}   // end function


/*  List_Container class  */
// List_Container implements Container
class List_Container : public Container {
    // standard-library list of doubles
    std::list<double> ld;
public :
    // empty list
    List_Container() {}
    //
    List_Container(initializer_list<double> il) : ld {il} {}
    // destructor
    ~List_Container() {}
    double& operator[](int i);
    //
    int size() const { return ld.size(); }
//private :
    };

// define operator[] function of List_Container
double& List_Container::operator[](int i) {
    for (auto& x : ld) {
        if (i == 0) {
            return x;
            }   //end if
        --i;
        }   // end for
    throw out_of_range("List_Container");
    }   // end definition operator[]

// use List_Container
void h() {
    List_Container lc = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    use(lc);
    }   // end function h

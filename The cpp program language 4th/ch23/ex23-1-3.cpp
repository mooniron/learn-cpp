/**************************************************************
* Name     :  ex23-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月12日
**************************************************************/



/*
example 23.3 : type checking
*/


template<Container Cont, typename Elem>
requires
// requirements for types Cont and Elem
Equal_comparable<Cont::value_type, Elem>()
// find the index of e in c
int find_index(Cont& c, Elem e)


// secgtion 23.3.1 : type equivalence
String<char> s1;
String<unsigned char> s2;
String<int> s3;
using Uchar = unsigned char;
using uchar = unsigned char;
String<Uchar> s4;
String<uchar> s5;
String<char> s6;
template<typename T, int N>
class Buffer;
Buffer<String<char>, 10> b1;
Buffer<char 10> b2;
Buffer<char, 20 - 10> b3;

// Circle* convert to Shape*
Shape* p {new Circle(p, 10)};
// error : no vector<Circle>* to vector<Shape>* conversion
vector<Shape>* q {new vector<Circle>{}};
// error : no vector<Circle> to vector<Shape> conversion
vector<Shape> vs {vector<Circle>{}};
// error : no vector<Circle*> to vector<Shape*> conversion
vector<Shape*> vs {vector<Circle*>{}};


// section 23.3.2 : error detection
template<typename T>
struct Link {
    Link* pre;
    // syntax error : missing semicolon
    Link* suc
    T val;
};

template<typename T>
class List {
    Link<T>* head;
public :
    .// error : pointer initialized with int
    List() : head {7} { }
    // error : undefined identifier o
    List(const T& t) : head {new Link<T> {0, o, t}} { }
    // ...
    void print_all() const;
};

template<typename T>
void List<T>::print_all() const
{
    // p depends on T
    for (Link<T>* p = head; p; p = p->suc) {
        // << depends on T
        cout << *p;
    }
}


class Rec {
    string name;
    string address;
};

void f(const List<int>& li, const List<Rec>& lr)
{
    li.print_all();
    lr.print_all();
}


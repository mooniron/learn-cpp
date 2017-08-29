/**************************************************************
* Name     :  ex27-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月18日
**************************************************************/



/*
example 27.3 : hierarchies of class templates
*/


// questionable example
template<typename Color_scheme, typename Canvas>
class Shape {
    // ...
};

template<typename Color_scheme, typename Canvas>
class Circle : public Shape {
    // ...
};

template<typename Color_scheme, typename Canvas>
class Triangle : public Shape {
    // ...
};

void user()
{
    auto p = new Triangle<RGB, Bitmapped>{{0, 0}, {0, 60}, {30, sqrt(60 * 60 - 30*30)}};
    // ...
}

class Shape {
    template<typename Color_scheme, typename Canvas>
    void configure(const Cor_scheme&, cvonst Canvan&);
    // ...
};


// section 27.3.1 : templates as interfaces
template<typename T>
class Vector<T*> : private Vector<void*>
{
    // ...
}


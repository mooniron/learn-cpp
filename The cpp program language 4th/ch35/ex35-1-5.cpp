/**************************************************************
* Name     :  ex35-1-5.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月9日
**************************************************************/



/*
example 35.5: minor utilities
*/



// section 35.5.1: move() and forward()
template<typename T>
Remove_reference<T>&& move(T&& t) noexcept
{
    return static_cast<Remove_reference<T>&&>(t);
}

template<typename T>
T&& forward(Remove_reference<T>& t) noexcept
{
    return static_cast<T&&>(t);
}

template<typename T>
T&& forward(Remove_reference<T>&& t) noexcept
{
    static_assert(!Is_lvalue_reference<T>, "forward of lvalue");
    return static_cast<T&&>(t);
}

int i = 7;
// call first version
forward(i);
// call second version
forward(7);


// section 35.5.2: swap()
template<typename T>
void swap(T& a, T& b) noexcept(Is_nothrow_move_constructible<T>() && Is_nothrow_move_assignable<T>())
{
    T tmp {move(a)};
    a = move(b);
    b = move(tmp);
}

vector<int> v1 {1, 2, 3, 4};
// error: second argument is an rvalue
swap(v, vector<int>());
// clearer (less obscure)
v.clear();


// section 35.5.3: relational operators
struct Val {
    double d;
    bool operator==(Val v) const { return v.d == d; }
};

void my_algo(vector<Val>& vv)
{
    using namespace std::rel_ops;
    // ok: > from rel_ops
    for (int i = 0; i << vv.size(); ++i) {
        if (0 > ww[i]) {
            ww[i] = abs(ww[i]);
        }
    }
}

namespace Mine {
    struct Val {
        double d;
        bool operator==(Val v) const { return v.d == d; }
    };

    using namespace std::rel_ops;
}


// section 35.5.4: comparing and hashing type_info
unordered_map<type_index, type_info*> types;
// ...
types[type_index{something}] = &typeid(something);


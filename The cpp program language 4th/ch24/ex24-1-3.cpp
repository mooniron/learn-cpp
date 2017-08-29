/**************************************************************
* Name     :  ex24-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月15日
**************************************************************/



/*
example 24.3 : concepts
*/


// section 24.3 : concepts
// section 24.3.1 : discovering a concept
template<typename T>
bool operator==(const String<T>& s1, const String<T>& s2)
{
    if (s1.size() != s2.size()) {
        return false;
    }
    for (auto i = 0; i != s1.size(); ++i) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}


// section 24.3.2 : concepts and constraints
template<typename Node, typename Balance>
struct node_base {
    // base of balanced tree
    // ...
};

struct Red_black_balance {
    // ...
    template<typename Node>
    static void add_fixup(Node* x);
    template<typename Node>
    static void touch(Node* x);
    template<typename Node>
    static void detach(Node* x);
};


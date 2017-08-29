/**************************************************************
* Name     :  ex24-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月15日
**************************************************************/



/*
example 24.1 : introduction
example 24.2 : algorithms and lifting
*/


// section 24.2 : algorithms and lifting
// one concrete algorithm on array of doules
double add_all(double* array, int n)
{
    double s {0.0};
    for (int i = 0; i < n; ++i) {
        s += array[i];
    }
    return s;
}

struct Node {
    Node* next;
    int data;
};

// another concrete algorithm on list of ints
int sum_elements(Node* first, Node* last)
{
    int s = 0;
    while (first != last) {
        s += first->data;
        first = first->next;
    }
    return s;
}

// concrete STL-like code
template<typename Iter, typename Val>
Val sum(Iter first, Iter last)
{
    Val s = 0;
    while (first != last) {
        s = s + *first;
        ++first;
    }
    return s;
}

double ad[] = {1, 2, 3, 4};
double s = sum<double*>(ad, ad + 4);

Node* operator++(Node* p)
{
    return p->next;
}

int operator*(Node* p)
{
    return p->data;
}

Node* end(Node*)
{
    return nullptr;
}

void test(Node* lst)
{
    int s = sum<int*>(lst, end(lst));
}


template<typename Iter, typename Val>
Val accumulate(Iter first, Iter last, Val s)
{
    while (first != last) {
        s = s + *first;
        ++first;
    }
    return s;
}

double ad[] = {1, 2, 3, 4};
// accumulate in a double
double s1 = accumulate(ad, ad + 4, 0.0);
// accumulate in an int
double s2 = accumulate(ad, ad + 4, 0);

template<typename Iter, typename Val, typename Oper>
Val accumulate(Iter first, Iter last, Val s, Oper op)
{
    while (first != last) {
        s = op(s, *first);
        ++first
    }
    return s;
}

double ad[] = {1, 2, 3, 4};
// as before
double s1 = accumulate(ad, ad + 4, 0.0, std::plus<double>);
double s2 = accumulate(ad, ad + 4, 1.0, std::multiply<double>);


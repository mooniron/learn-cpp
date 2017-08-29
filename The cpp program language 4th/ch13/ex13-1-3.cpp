/**************************************************************
* Name     :  ex13-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月23日
**************************************************************/



/*
example 13.1 : error handling
    section 13.1.4 : alternative view of exceptions
*/


void fnd(Tree* p, const string& s)
{
    // found s
    if (s == p->str) {
        throw p;
    }
    if (p->left) {
        fnd(p->left, s);
    }
    if (p->right) {
        fnd(p->right, s);
    }
}

Tree* find(Tree* p, const string& s)
{
    try {
        fnd(p, s);
    }
    // q->str == s
    catch (Tree* q) {
        return q;
    }
    return 0;
}

/**************************************************************
* Name     :  ex12-1-11 s.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年5月18日
**************************************************************/



/*
example pointer to function
*/


void error(string s)
{
    /* ... */
}

// pointer to function taking a string argument and returning nothing
void (*efct)(string);

void f()
{
    // efct points to error
    efct = &error;
    // call error through efct
    efct("error");
}


// ok : same as = error
void (*f1)(string) = &error;
// ok : same as = &error
void (*f2)(string) = error;

void g()
{
    // ok : same as (*f1)("Vasa")
    f1("Vasa");
    // ok : as f1("Mary Rose")
    (*f1)("Mary Rose");
    // ...
}

// pointer to void(string)
void (*pf)(string);
// void(string)
void f1(string);
// int(string)
int f2(string);
// void(int*)
void f3(int*);

void f()
{
    // ok
    pf = &f1;
    // error : bad return type
    pf = &f2;
    // error : bad argument type
    pf = &f3;
    // ok
    pf("Hera");
    // error : bad argument type
    pf(1);
    // error : void assigned to int
    int i = pf("Zeus");
}


using P1 = int(*)(int*);
using P2 = void(*)(void);

void f(P1 pf)
{
    P2 pf2 = reinterpret_cast<P2>(pf);
    // likely serious problem
    pf2();
    // convert pf2 "back again"
    P1 pf1 = reinterpret_cast<P1>(pf2);
    int x = 7;
    // ok
    int y = pf1(&x);
    // ...
}


// comparison operation
using CFT = int(const void*, const void*);
/*
sort the "n" elements of vector "base" into increasing order
using the comparison function pointed to by "cmp".
the elements are of size "sz".
shell sort
*/
void ssort(void* base, size_t n, size_t sz, CFT cmp)
{
    for (int gap = n / 2; 0 < gap; gap /= 2) {
        for (int i = gap; i != n; i++) {
            for (int j = i - gap; 0 <= j; j -= gap) {
                // necessary cast
                char* b = static_cast<char*>(base);
                // &base[j]
                char* pj = b + j * sz;
                // &base[j + gap]
                char* pjg = b + (j + gap) * sz;
                // swap base[j] and base[j + gap]
                if (cmp(pjg, pj) < 0) {
                    // swap
                    for (int k = 0; k != sz; k++) {
                        char temp = pj[k];
                        pj[k] = pjg[k];
                        pjg[k] = temp;
                    }
                }
            }
        }
    }
}


struct User {
    const char* name;
    const char* id;
    int dept;
};

vector<User> heads = {
    "Ritchie D.M.", "dmr", 11271,
    "Sethi R.", "ravi", 11272,
    "Szymanski T.G.", "tgs", 11273,
    "Schryer N.L.", "nls", 11274,
    "Schryer N.L.", "nls", 11275,
    "Kernighan B.W.", "bwk", 11276
};

void print_id(vector<User>& v)
{
    for (auto& x : v) {
        cout << x.name << '\t' << x.id << 't' << x.dept << '\n';
    }
}

// comparison
// compare name strings
int cmp1(const void* p, const void* q)
{
    return strcmp(static_cast<const User*>(p)->name, static_cast<const User*>(q)->name);
}

// compare dept numbers
int cmp2(const void* p, const void* q)
{
    return static_cast<const User*>(p)->name - static_cast<const User*>(q)->dept;
}

// bad
// compare ids
int cmp3(const User* p, const User* q)
{
    return strcmp(p->id, q->id);
}


int main()
{
    cout << "Heads in alphabetical order : \n";
    ssort(heads, 6, sizeof(User), cmp1);
    print_id(heads);
    cout << '\n';

    cout << "Heads in order of department number: \n";
    ssort(heads, 6, sizeof(User), cmp2);
    print_id(heads);

    // elegant c++ version
    cout << "Heads in alphabetical order : \n";
    sort(heads.begin(), heads.end(),
        [](const User& x, const User& y) { return x.name < y.name}
    );
    print_id(heads);
    cout << '\n';

    cout << "Heads in order of department number : \n";
    sort(heads.begin(), head.end(),
        [](const User& x, const User& y) { return x.dept < y.dept; }
    );
    print_id(heads);

    sort(heads, [](const User& x, const User& y) { return x.name < y.name; });
}


void f(int);
int f(char);

// void f(int)
void (*pf1)(int) = &f;
// int f(char)
int (*pf2)(char) = &f;
// error : no void f(char)
void (*pf3)(char) = &f;

void f(int) noexcept;
void g(int);

// ok : but we throw away useful information
void (*p1)(int) = f;
//ok : we preserve the noexcept information
void (*p2)(int) noexcept = f;
// error : we don't know that g doesn't throw
void (*p3)(int) noexcept = g;


// error : linkage specification in alias
using Pc = extern "C" void(int);
// error : noexcept in alias
using Pn = void(int) noexcept;

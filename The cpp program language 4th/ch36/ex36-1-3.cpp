/**************************************************************
* Name     :  ex36-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月11日
**************************************************************/



/*
example 36.3: strings
*/



template<typename C, typename Tr =char_traits<C>, typename A = allocator<C>>
class basic_string {
public:
    using traits_type = Tr;
    using value_type = typename Tr::char_type;
    using allocator_type = A;
    using size_type = typename allocator_traits<A>::size_type;
    using difference_type = typename allocator_traits<A>::difference_type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename allocator_traits<A>::pointer;
    using const_pointer = typename allocator_traits<A>::const_pointer;
    using iterator = /* implementation-defined */;
    using const_iterator = /*implementation-defined */;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    // integer representing end-of-string
    static const size_type npos = −1;
    //...
};

using string = basic_string<char>;
using u16string = basic_string<char16_t>;
using u32string = basic_string<char32_t>;
using wstring = basic_string<wchar_t>;


// section 36.3.1: string vs. C-style strings
string address(const string& identifier, const string& domain)
{
    return identifier + '@' + domain;
}

void test()
{
    string t = address("bs", "somewhere");
    cout << t << '\n';
}


char* address(const char* identifier, const char* domain)
{
    int iden_len = strlen(identifier);
    int dom_len = strlen(domain);
    // remember space for 0 and @'
    char* addr = (char*) malloc(iden_len + dom_len + 2);
    strcpy(addr, identifier);
    addr[iden_len] = '@';
    strcpy(addr+iden_len+1, domain);
    return addr;
}

void test2()
{
    char* t = address("bs", "somewhere");
    printf("%s\n", t);
    free(t);
}

void test3()
{
    string s1 = "Ring";
    if (s1 != "Ring") {
        insanity();
    }
    if (s1 < "Opera") {
        cout << "check";
    }

    string s2 = address(s1, "Valkyrie");

    char s3[] = "Ring";
    if (strcmp(s3, "Ring") != 0) {
        insanity();
    }
    if (strcmp(s3, "Opera") < 0) {
        cout << "check";
    }

    char* s4 = address(s3, "Valkyrie");
    free(s4);
}

void test4()
{
    vector<string> vs = {"Grieg", "Williams", "Bach", "Handel"};
    // assuming that I haven't defined sort(vs)
    sort(bs.begin(), vs.end());

    const char* as[] = {"Grieg", "Williams", "Bach", "Handel"};
    qsort(as, sizeof(*as), sizeof(as)/sizeof(*as), (int(*)(const void*, const void*))strcmp);
}


// section 36.3.2: constructors
// the empty string
string s0;
// construct from C-style string
string s1 {"As simple as that!"};
// copy consgtructor
string s2 {s1};

// error: no string(int)
string s3 {7};
// error
string s4 {'a'};
// ok: 7 'a's
string s5 {7, 'a'};
// danger: passing nullptr
string s6 {0};
// bad: set p to "no string"
const char* p = 0;
// may or may not be ok depending on the value of p
string s7 {p};
// ok: pass pointer to C-style string
string s8 {"OK"};

// throw length_error
string s9 {string::npos, 'x'};
string ss {"Fleetwood Mac"};
// "Fleetwood"
string ss2 {ss, 0, 9};
// "Mac"
string ss3 {ss, 10, string::npos};


// section 36.3.3: fundanmental operations
// use as as target for low-level input
void fill(istream& in, string& s, int max)
{
    // make sure there is enough allocated space
    s.reserve(max);
    in.read(&s[0], max);
    // number of characters read
    const int n = in.gcount();
    // discard excess capacity
    s.resize(n);
    s.shrink_to_fit();
}


// section 36.3.4: string I/O
vector<string> lines;
for (string s; getline(cin, s); ) {
    lines.push_back(s);
}

string first_name;
string second_name;
cin >> first_name >> second_name;


// section 36.3.5: numeric conversions
string s = "123.45";
// x1 = 123
auto x1 = stoi(s);
// x2 = 123.45
auto x2 = stod(s);

string ss = "123.45678901234";
// put number of characters read here
size_t dist = 0;
// x = 123
auto x = stoi(ss, &dist);
// ignore the dot
++dist;
// y = 45678901234 (a long long)
auto y = stoll(&ss[dist]);

string s = "123.45";
// x1 = 123
auto x1 = stoi(s);

string s4 = "149F";
// x5 = 149
auto x5 = stoi(s4);
// x6 = 149
auto x6 = stoi(s4, nullptr, 10);
// x7 = 014
auto x7 = stoi(s4, nullptr, 8);
// x8 = 0x149F
auto x8 = stoi(s4, nullptr, 16);

// binary
string s5 = "1100101010100101";
// x9 = 0xcaa5
auto x9 = stoi(s5, nullptr, 2);

// throws std::invalid_argument
stoi("Hello, World!");
// throws std::out_of_range;
stoi("12345678901234567890");
// throws std::out_of_range; errno = ERANGE
stof("123456789e1000");


// section 36.3.6: STL-like operations
void f(string& s)
{
    auto p = find_if(s.begin(), s.end(), islower);
    // ...
}

// add middle name
void add_middle(string&  s, const string& middle)
{
    auto p = s.find(' ');
    s.insert(p, ' ' + middle);
}

void test()
{
    string dmr = "Dennis Ritchie";
    add_middle(dmr, "MacAlistair");
    cout << dmr << '\n';
}

void f()
{
    string s = "but I have heard it works even if you don't believe in it";
    // erase initial "but "
    s.replace(0, 4, "");
    s.replace(s.find("even"), 4, "only");
    // erase by replacing with ""
    s.replace(s.find("don't"), 6, "")
    assert(s == "I have heard it works only if you believe in it");
}

void f2()
{
    string s = "but I have heard it works even if you don't believe in it";
    s.replace(0, 4, "").replace(s.find("even"), 4, "only").replace(s.find("don't"), 6, "");
    assert(s == "I have heard it works only if you believe in it");
}


// section 36.3.7: the find family
void f()
{
    string s {"accdcde"};

    // i1 == 2
    auto i1 = s.find("cd");
    // i2 = 4
    auto i2 = s.rfind("cd");
    // i3 == 1
    auto i3 = s.find_first_of("cd");
    // i4 == 5
    auto i4 = s.find_last_of("cd");
    // i5 == 0
    auto i5 = s.find_first_not_of("cd");
    // i6 == 6
    auto i6 = s.find_last_not_of("cd");
}


// section 36.3.8: substrings
void user()
{
    string s = "Mary had a little lamb";
    // s2 == "Mary"
    string s2 = s.substr(0, 4);
    // does not change s
    s2 = "Rose";
}

void f()
{
    string s = "Mary had a little lamb";
    // s2 == "Mary"
    string s2  = s.substr(0, 4);
    // i1 is positive
    auto i1 = s.compare(s2);
    // i2 == 0
    auto i2 = s.compare(0, 4, s2);
}


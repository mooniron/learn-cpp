/**************************************************************
* Name     :  ex31-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年7月30日
**************************************************************/



/*
example 31.4: containers
*/



// section 31.4.1: vector
template<typename T, typename Allocator = allocator<T>> {
public:
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = /*implementation defined */;
    using const_iterator = /*implementation-defined */;
    using size_type = /* implementation-defined */;
    using difference_type = /* implementation-defined*/;
    using value_type = T;
    using allocator_type = Allocator;
    using pointer = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    // ...
};


// vector and Growth
// input "buffer" for characters
vector<char> chars;
constexpr int max = 20000;
chars.reserve(max);
// pointers to start of words
vector<char*> words;
bool in_word = false;
for (char c; cin.get(c); ) {
    if (isalpha(c)) {
        if (!in_word) {
            // found beginning of word
            in_word = true;
            // end of previous word
            chars.push_back(0);
            chars.push_back(c);
            words.push_back(&chars.back());
        }
        else {
            chars.push_back(c);
        }
    }
    else {
        in_word = false;
    }
}

// terminate last word
if (in_word) {
    chars.push_back(0);
}
if (max < chars.size()) {
    // oops: chars grew beyond capacity: the words are invalid
    // ...
}
chars.shrink_to_fit();


// section 31.4.1.2: vector and nesting
// section 31.4.1.3: vector and arrays
void read()
{
    array<int, MAX> a;
    for (auto& x : a) {
        cin.get(&x);
    }
}


// section 31.4.1.4: vector and string


// section 31.4.2: lists
void use()
{
    list<int> lst {2, 3, 2, 3, 5};
    // lst is now {2, 2, 5}
    lst.remove(3);
    // lst is now {2, 5}
    lst.unique();
    // writes 2
    cout << lst.size() << '\n';
}

list<int> lst1 {1, 2, 3};
list<int> lst2 {5, 6, 7};

auto p = lst1.begin();
// p points to 2
++p;
auto q = lst2.begin();
// q points to 6;
++q;
// lst1 is now {1, 5, 6, 7, 2, 3}, lst2 is now {}
lst1.splice(p, lst2);
// p still points to 2 and q still points to 6



// section 31.4.3: associative containers
// section 31.4.3.1: ordered associative containers
template<typename Key, typename T, typename Compare = less<Key>, typename Allocator = allocator<pair<const Key, T>>>
class map {
public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = pair<const Key, T>;
    using key_compare = Compare;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = /* implementation-defined */;
    using const_iterator = /* implementation-defined */;
    using size_type = /* implementation-defined */;
    using difference_type = /* implementation-defined */;
    using pointer = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    class value_compare {
        /* operator()(k1, k2) does a key_compare()(k1, k2) */
    };
    // ...
};


map<string, string> dictionary;
// insert or assign to element
dictionary["seal"] = "large body of water";
// read value
cout << dictionary["seal"];

auto q = dictionary.find("seal");
if (q == dictionary.end()) {
    cout << "entry not found";
    dictionary.insert(make_pair("seal", "eats fish"));
}
else {
    cout q->second;
}

dictionary.emplace("seal", "extinct");

multimap<stirng, int> mm {
    {"apple", 2},
    {"pear", 2},
    {"apple", 7},
    {"orange", 2},
    {"apple", 9}
};

const string k {"apple"};
auto pp = mm.equal_range(k);
if (pp.first == pp.second) {
    cout << "no element with value '" << k << "'\n";
}
else {
    cout << "elements with value '" << k << "':\n";
    for (auto p = pp.first(); p != pp.second; ++p) {
        cout << p->second << ' ';
    }
}

auto pp = make_pair(m.lower_bound(), m.upper_bound());
// ...

struct Record {
    string label;
    int value;
};

bool operator<(const Record& a, const Record& b)
{
    return a.label < b.label;
}

set<Record> mr {{"duck", 10}, {"pork", 12}};

void read_test()
{
    for (auto& r : mr) {
        cout << '{' << r.label << ':' << r.value << '}';
    }
    cout << endl;
}

void modify_test()
{
    for (auto& r : mr) {
        // error: set elements are immutable
        ++r.value;
    }
}


// section 31.4.3.2: unordered associative containers
unordered_map<string, int> score1 {
    {"andy", 7},
    {"al", 9},
    {"bill", -3},
    {"barbara", 12}
};

map<string, int> score2 {
    {"andy", 7},
    {"al", 9},
    {"bill", -3},
    {"barbara", 12}
};

template<typename X, typename Y>
ostream& operator<<(ostream& os, pair<X, Y>& p)
{
    return os << '{' << p.first << ',' << p.second << '}';
}

void user()
{
    cout << "unordered: ";
    for (const auto& x : score1) {
        cout << x << ", ";
    }
    cout << "\nordered: ";
    for (const auto& x : score2) {
        cout << x << ", ";
    }
}


// section 31.4.3.3: constructing unordered_maps
template<typename Key, typename T, typename Hash = hash<Key>, typename Pred = std::equal_to<Key>, typename Allocator = std::allocator<std::pair<const Key, T>>>
class unordered_map {
public:
    using key_type = Key;
    using value_type = std::pair<const Key, T>;
    using mapped_type = T;
    using hasher = Hash;
    using key_equal = Pred;
    using allocator_type = Allocator;
    using pointer = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = /* implementation-defined */;
    using difference_type = /* implementation-defined*/;
    using iterator = /* implementation-defined*/;
    using const_iterator = /* implementation-defined*/;
    using local_iterator = /* implementation-defined*/;
    using const_local_iterator = /* implementation-defined*/;
    // ...
};

// ok
map<string, int> m {My_comparator};
// error
unordered_map<string, int> um {My_hasher};
// ok
unordered_map<string, int> um {100, My_hasher};


// section 31.4.3.4: hash and equality functions
struct Record {
    string name;
    int val;
};

struct Nocase_hash {
    // shift code d number of bits in each iteration
    int d = 1;
    size_t operator()(const Record& r) const
    {
        size_t h = 0;
        for (auto x : r.name) {
            h <<= d;
            h ^= toupper(x);
        }

        return h;
    }
};

struct Nocase_equal {
    bool operator()(const Record& r, const Record& r2) const
    {
        if (r.name.size() != r2.name.size()) {
            return false;
        }

        for (int i = 0; i < r.name.size(); ++i) {
            if (toupper(r.name[i]) != toupper(r2.name[i])) {
                return false;
            }
        }
        return true;
    }
}


unordered_set<Record, Nocase_hash, Nocase_equal> m {
    {{"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}},
    Nocase_hash{2},
    Nocase_equal{}
};

for (auto r : m) {
    cout << "{" << r.name << ',' << r.val << "}\n";
}

// use Nocase_hash{} and Nocase_equal{}
unordered_set<Record, Nocase_hash, Nocase_equal> m {
    {{"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}},
};


size_t hf(const Record& r)
{
    return hash<string>()(r.name) ^ hash<int>()(r.val);
}

bool eq(const Record& r, const Record& r2)
{
    return r.name == r2.name && r.val == r2.val;
}


unordered_set<Record, decltype(&hf), decltype(&eq)> m {
    {{"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}},
    hf,
    eq
};

for (auto r : m) {
    cout << "{" << r.name << ',' << r.val << "}\n";
}

unordered_set<Record, decltype(&hf), decltype(&eq)> m {10, hf, eq};

unordered_set<
    Record,     // value type
    function<size_t(const Record&)>,    // hash type
    function<bool(const, Record&, const Record&)>   // equal type
> m {
    10,
    [](const Record& r) { return hash<stirng>{}(r.name) ^ hash<int>{}(r.val); },
    [](const Record& r, const Record& r2) { return r.name == r2.name && r.val == r2.val; }
};


auto hf = [](const Record& r) { return hash<stirng>{}(r.name) ^ hash<int>{}(r.val); };
auto eq = [](const Record& r, const Record& r2) { return r.name == r2.name && r.val == r2.val; };

unordered_set<Record, decltype(hf), decltype(eq)> m {10, hf, eq};


namespace std {
    template<>
    struct hash<Record> {
        size_t operator()(const Record& r) const
        {
            return hash<stirng>{}(r.name) ^ hash<int>{}(r.val);
        }
    };
    template<>
    struct equal_to<Record> {
        bool operator()(const Record& r, const Record& r2) const
        {
            return r.name == r2.name && r.val == r2.val;
        }
    };
}


unordered_set<Record> m1;
unordered_set<Record> m2;


// section 31.4.3.5: load and buckets

unordered_set<Record,
    [](const Record& r) { return hash(r.name); }
> people;
// ...
// expected maximum number of elements
constexpr int expected = 1000000;
// at most 70% full
people.max_load_factor(0.7);
// about 1,430,000 buckets
people.reserve(expected);


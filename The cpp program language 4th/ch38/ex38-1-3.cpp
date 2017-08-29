/**************************************************************
* Name     :  ex38-1-3.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月14日
**************************************************************/



/*
example 38.2: the  I/O stream
*/



// section 38.2.1: file streams
template<typename C, typename Tr = char_traits<C>>
class basic_fstream : public basic_iostream<C, Tr> {
public:
    using char_type = C;
    using int_type = typename Tr::int_type;
    // ...
};

using ifstream = basic_ifstream<cahr>;
using wifstream = basic_ifstream<wchar_t>;
using ofstream = basic_ofstream<cahr>;
using wofstream = basic_ofstream<wchar_t>;
using fstream = basic_fstream<cahr>;
using wfstream = basic_fstream<wchar_t>;

// "o" for "output" implying ios::out
ofstream ofs("target");
if (!ofs) {
    error("could't open 'target' for writing");
}

// "i" for "input" implying ios::in
fstream ifs;
ifs.open("source", ios_base::in);
if (!ifs) {
    error("couldn't open 'source' for reading");
}


// section 38.2.2: string streams
template<typename C, typename Tr = char_traits<C>, typename A = allocator<C>>
class basic_stringstream : public basic_iostream<C, Tr> {
public:
    using char_type = C;
    using int_type = typename Tr::int_type;
    // for positions in string
    using pos_type = typename Tr::pos_type;
    // for offsets in string
    using off_type = typename Tr::off_type;
    using  traits_type = Tr;
    using allocator_type = A;
    // ...
};

using istringstream = basic_istringstream<char>;
using wistringstream = basic_istringstream<wchar_t>;
using ostringstream = basic_ostringstream<char>;
using wostringstream = basic_ostringstream<wchar_t>;
using stringstream = basic_stringstream<char>;
using wstringstream = basic_stringstream<wchar_t>;


void test()
{
    // write at end
    ostringstream oss {"Label: ", ios::ate};
    // writes "Label: "
    cout << oss.str() << '\n';
    oss << "val";
    // writes "Label: val" ("val" appended after "Label: ")
    cout << oss.str() << '\n';
    // write at beginning
    ostringstream oss2 {"Label: "}
    // writes "Label: "
    cout << oss2.str() << '\n';
    oss2 << "val";
    // writes "valel: " (val overwrites "Label: ")
    cout << oss2.str() << '\n';
}

void test2()
{
    istringstream iss;
    // fill iss
    iss.str("Foobar");
    // writes 1
    cout << iss << '\n';
    // ok: writes "Foobar"
    cout << iss.str() << '\n';
}

// the last operation of iss succeeded: iss's state is good() or eof()
if (iss) {
    // ...
}
else {
    // handle problem
}


/**************************************************************
* Name     :  ex38-1-7.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月20日
**************************************************************/



/*
example 38.6: buffering
*/


template<typename C, typename Tr = char_traits<C>>
class basic_streambuf {
public:
    using char_type = C;
    using int_type = typename Tr::int_type;
    // ..
    virtual ~basic_streambuf();
};

using streambuf = basic_streambuf<char>;
using wstreambuf = basic_streambuf<wchar_t>;


// section 38.6.1: output streams and buffers
template<typename C, typename Tr = char_traits<C>>
class basic_ostream : virtual public basic_ios<C, Tr>
{
public:
    // ...
    explicit basic_ostream(basic_streambuf<C, Tr>* b);
    // get current position
    pos_type tellp();
    // set current position
    basic_ostream& seekp(pos_type);
    // set current position
    basic_ostream& seekp(off_type, ios_base::seekdir);
    // empty buffer (to real destination)
    basic_ostream& flush();
    // write from b
    basic_ostream& operator<<(basic_streambuf<C, Tr>* b);
}

// fout refers to some file
int f(ofstream& fout)
{
    fout << "0123456789";
    // 8 from begining
    fout.seekp(8);
    // add '#' and move position (+1)
    fout << '#';
    // 4 backward
    fout.seekp(-4, ios_base::cur);
    // add '*' and move position (+1)
    fout << '*';
}


// section 38.6.2: input streams and buffers
template<typename C, typename Tr = char_traits<C>>
class basic_istream : virtual basic_ios<C, Tr> {
public:
    // ...
    explicit basic_istream(basic_streambuf<C, Tr>* b);
    // get current position
    pos_type tellg();
    // set current position
    basic_istream& seekg(pos_type);
    // set current position
    basic_istream& seekg(off_type, ios_base::seekdir);
    // put c back into the buffer
    basic_istream& putback(C c);
    // put back most recent char read
    basic_istream& unget();
    // look at next character to beread
    int_type peek();
    // clear buffer(flush)
    int sync();
    // read into b
    basic_istream& operator>>(basic_streambuf<C, Tr>* b);
    basic_istream& get(basic_streambuf<C, Tr>* b, C t = Tr::newline());
    // read at most n char
    streamsize readsome(C* p, streamsize n);
};


// section 38.6.3: buffer iterators
// section 38.6.3.1: istreambuf_iterator
template<typename C, typename Tr = char_traits<C>>
class istreambuf_iterator : public iterator<input_iterator_tag, C, typename Tr::off_type, C> {
public:
    using char_type = C;
    // ...
    using streambuf_type = basic_streambuf<C, Tr>;
    using istream_type = basic_istream<C, Tr>;
    // ...
};


// section 38.6.3.2: ostreambuf_iterator

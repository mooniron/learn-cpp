/**************************************************************
* Name     :  ex38-1-2.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月14日
**************************************************************/



/*
example 38.1: introduction
*/



template<typename C, typename Tr = char_traits<C>>
class basic_iostream : public basic_istream<C, Tr>, public basic_ostream<C, Tr> {
public:
    using char_type = C;
    using int_type = typename Tr::int_type;
    using pos_type = typename Tr::pos_type;
    // ...
    explicit basic_iostream(basic_streambuf<C, Tr>* sb);
    virtual  ~basic_iostream();
protected:
    basic_iostream(const basic_iostream& rhs) = delete;
    basic_iostream(basic_iostream&& rhs);
    basic_iostream& operator=(const basic_iostream& rhs) = delete;
    basic_iostream& operator=(basic_iostream&& rhs);
    void swap(basic_iostream& rhs);
};


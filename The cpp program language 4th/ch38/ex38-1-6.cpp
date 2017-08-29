/**************************************************************
* Name     :  ex38-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月20日
**************************************************************/



/*
example 38.5: stream iterators
*/


template<typename T, typename C = char, typename Tr = char_traits<C>, typename Distance = ptrdiff_t>
class istream_iterator : public iterator<input_iterator_tag, T, Distance, const T*, const T&> {
    using char_type = C;
    using traits_type = Tr;
    using istream_type = basic_istream<C, Tr>;
    // ...
};

template<typename T, typename C = char, typename Tr = char_traits<C>>
class ostream_iterator : public iterator<output_iterator_tag, void, void, void, void> {
    using char_type = C;
    using traits_type = Tr;
    using ostream_type = basic_ostream<C, Tr>;
    // ...
};

copy(istream_iterator<double>{cin}, istream_iterator<double, char>{}, ostream_iterator<double>{cout, ";\n"});

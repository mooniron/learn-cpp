/**************************************************************
* Name     :  ex34-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月8日
**************************************************************/



/*
example 34.6: uninitialized memory
*/



// section 34.6.1: temporary buffers
// allocate, don't initialize
template<typename T>
pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t);
// deallocate, don't destroy
template<typename T>
void return_temporary_buffer(T*);


// section 34.6.2: raw_storage_iterator
template<typename Out, typename T>
class raw_storage_iterator : public iterator<output_iterator_tag, void, void, void, void> {
    Out p;
public:
    explicit raw_storage_iterator(Out pp) : p {pp} { }
    raw_storage_iterator& operator*() { return *this; }
    raw_storage_iterator& operator=(const T& val)
    {
        // place val in *p
        new(&*p) T{val};
        return *this;
    }

    raw_storage_iterator& operator++()
    {
        ++p;
        // pre-increment
        return *this;
    }

    // post-increment
    raw_storage_iterator operator++(int)
    {
        auto t = *this;
        ++p;
        return t;
    }
};


void test1()
{
    // get uninitialized space
    auto pp =  get_temporary_buffer<string>(1000);
    if (pp.second < 1000) {
        // ... handle allocation failure ...
    }

    // the iterator
    auto p = raw_storage_iterator<string*, string>(pp.first);
    generate_n(p, a.size(),
        [&]{ next_permutation(seed, seed + size(seed) - 1); return seed; }
    );
    // ...
    return_temporary_buffer(p);
}



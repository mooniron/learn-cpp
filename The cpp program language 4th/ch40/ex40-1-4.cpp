/**************************************************************
* Name     :  ex40-1-4.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年8月22日
**************************************************************/



/*
example 40.4: complex numbers
*/


// a complex is a pair of scalar values, basically a coordinate pair
template<typename Scalar>
class complex {
    Scalar re,im;
public:
    complex(const Scalar& r = Scalar{}, const Scalar& i = Scalar{})
        : re(r), im(i) { }
    Scalar real() const { return re; }
    void real(Scalar r) { re = r; }
    Scalar imag() const { return im; }
    void imag(Scalar i) { im = i; }
    template<typename X>
    complex(const complex<X>&);
    // ...
};



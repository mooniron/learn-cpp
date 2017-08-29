// Vector class declaration
class Vector {
public :
    Vector(int s);
    double& operator[](int i);
    int size();
private :
    // elem : point to an array of sz doubles
    double* elem;
    int sz;
};



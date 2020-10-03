#include <iostream>

template<typename X>
class Base {
    public:
    int basefield;
    typedef int T;
};

class D1 : public Base<Base<void>> // not a template case
{
    public:
    void f() {basefield = 3;}
};

template <typename T>
class D2 : public Base<double> // Base<double> is non-dependent base
{
    public:
    void f() {basefield = 7;}
    T strange; // T is taken from the Base::T, which is int
};

void g(D2<int *> &d2, int* p)
{
    // d2.strange = p; // ERROR: a value of type "int *" cannot be assigned to an entity of type "int"
}

int main()
{

}


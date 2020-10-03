

template <typename X>
class Base
{
public:
    int basefield;
    typedef int T;
};

template <typename T>
class DD : public Base<T>
{
public:
    void f() { basefield = 0; }
};

template <>
class Base<bool>
{
public:
    enum
    {
        basefield = 42
    };
};

void g(DD<bool> &d) // with specialization, basefield is an enum constant, thus can't be re-assigned in f()
{
    // d.f(); // '=': cannot convert from 'int' to 'Base<bool>::<unnamed-enum-basefield>' 
}

int main()
{
    
}




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

void g(DD<bool> &d)
{
    d.f();
}

int main()
{
    
}


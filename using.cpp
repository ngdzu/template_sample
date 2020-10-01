#include <iostream>

namespace N{
    class X{

    };

    template<int I> void select(X*)
    {
        std::cout << I << std::endl;
    }
}

void g(N::X* xp)
{
    N::select<3>(xp); 
}

int main()
{
    N::X obj{};
    g(&obj);
}




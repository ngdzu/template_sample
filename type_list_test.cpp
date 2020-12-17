
#include <type_traits>
#include <cassert>
#include "type_list.hpp"
#include "GenScatterHierarchy.hpp"
#include "type_utils.hpp"

#include <iostream>

template <typename T>
struct Holder
{
    T value_;
};

using basic_type = TYPE_LIST_4(char, short, int, long);

using WidgetInfo = GenScatterHierarchy<basic_type, Holder>;

int main()
{
    // using basic_type = TYPE_LIST_4(char, short, int, long);
    // Append<NullType, int>;

    // Append<TYPE_LIST_2(int, double), char>::Result;

    static_assert(Length<basic_type>::value == 4);

    static_assert(Length<typename Append<basic_type, unsigned char>::Result>::value == 5);
    static_assert(Length<typename Append<TYPE_LIST_1(int), double>::Result>::value == 2);

    static_assert(std::is_same_v<TypeAt<basic_type, 0>::Result, char>);
    static_assert(std::is_same_v<TypeAt<basic_type, 1>::Result, short>);
    static_assert(std::is_same_v<TypeAt<basic_type, 2>::Result, int>);
    static_assert(std::is_same_v<TypeAt<basic_type, 3>::Result, long>);

    using int_type_plus_double = typename Append<basic_type, double>::Result;
    static_assert(std::is_same_v<TypeAt<int_type_plus_double, 4>::Result, double>);

    // index out of bound, return NullType
    static_assert(std::is_same_v<TypeAt<int_type_plus_double, 1000>::Result, NullType>);

    static_assert(IndexOf<basic_type, double>::value == -1);
    static_assert(IndexOf<basic_type, float>::value == -1);
    static_assert(IndexOf<basic_type, char>::value == 0);
    static_assert(IndexOf<basic_type, short>::value == 1);
    static_assert(IndexOf<basic_type, int>::value == 2);
    static_assert(IndexOf<basic_type, long>::value == 3);
    static_assert(IndexOf<int_type_plus_double, char>::value == 0);
    static_assert(IndexOf<int_type_plus_double, short>::value == 1);
    static_assert(IndexOf<int_type_plus_double, int>::value == 2);
    static_assert(IndexOf<int_type_plus_double, long>::value == 3);
    static_assert(IndexOf<int_type_plus_double, double>::value == 4);

    WidgetInfo obj;
    Field<short>(obj).value_ = 3;

    Field<2>(obj).value_ = 4;

    {
        int a = Field<short>(obj).value_;
        int b = Field<2>(obj).value_;
        assert(a == 3);
        assert(b == 4);
    }

    using MyType = TYPE_LIST_4(int, float, double, int);
    using MyTypeNoDup = typename NoDuplicates<MyType>::Result;
    using NoDupType = TYPE_LIST_3(int, float, double);
    static_assert(std::is_same_v<MyTypeNoDup, NoDupType>);

    std::cout << "hello world" << std::endl;

    return 0;
}

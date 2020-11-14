#include <typeinfo>

template<typename T>
struct eval_t;

#define EVAL(E) eval_t<E>

// Compound types are types constructed by other types

// primary template
template <typename T>
class CompoundT
{
public:
    enum
    {
        IsPtrT = 0,
        IsRefT = 0,
        IsArrayT = 0,
        IsFuncT = 0,
        IsMemPtrT = 0
    };

    using BaseT = T;
    using BottomT = T;
    using classT = CompoundT<void>;
};

// reference
template <typename T>
class CompoundT<T &>
{
public:
    enum
    {
        IsPtrT = 0,
        IsRefT = 1,
        IsArrayT = 0,
        IsFuncT = 0,
        IsMemPtrT = 0
    };
    using BaseT = T;
    using BottomT = typename CompoundT<T>::BottomT; // NOTE: use typename
    using classT = CompoundT<void>;
};

// pointer
template <typename T>
class CompoundT<T *>
{
public:
    enum
    {
        IsPtrT = 1,
        IsRefT = 0,
        IsArrayT = 0,
        IsFuncT = 0,
        IsMemPtrT = 0
    };
    
    using BaseT = T;
    using BottomT = typename CompoundT<T>::BottomT; // NOTE: use typename
    using classT = CompoundT<void>;
};

// array
template <typename T, size_t N>
class CompoundT<T[N]>
{
public:
    enum
    {
        IsPtrT = 0,
        IsRefT = 0,
        IsArrayT = 1,
        IsFuncT = 0,
        IsMemPtrT = 0
    };
};

// empty array
template <typename T>
class CompoundT<T[]>
{
public:
    enum
    {
        IsPtrT = 0,
        IsRefT = 0,
        IsArrayT = 1,
        IsFuncT = 0,
        IsMemPtrT = 0
    };
};

// pointer to member
template <typename T, typename C>
class CompoundT<T C::*> // T is type, C is class name. for example: int Widget::* lineEdit;
{
public:
    enum
    {
        IsPtrT = 0,
        IsRefT = 0,
        IsArrayT = 0,
        IsFuncT = 0,
        IsMemPtrT = 1
    };
};

class Sample
{
public:
    float n;
};

int main()
{
    static_assert(CompoundT<int>::IsPtrT == false);
    static_assert(CompoundT<int>::IsRefT == false);
    static_assert(CompoundT<int>::IsArrayT == false);
    static_assert(CompoundT<int>::IsFuncT == false);
    static_assert(CompoundT<int>::IsMemPtrT == false);

    static_assert(CompoundT<int &>::IsPtrT == false);
    static_assert(CompoundT<int &>::IsRefT == true);
    static_assert(CompoundT<int &>::IsArrayT == false);
    static_assert(CompoundT<int &>::IsFuncT == false);
    static_assert(CompoundT<int &>::IsMemPtrT == false);

    // CompoundT<int &> c_intRef;
    // EVAL(CompoundT<int &>::BottomT) a;
    // EVAL(CompoundT<int &>::classT) b;
    // EVAL(CompoundT<int &>::BaseT) b;
    

    static_assert(CompoundT<int *>::IsPtrT == true);
    static_assert(CompoundT<int *>::IsRefT == false);
    static_assert(CompoundT<int *>::IsArrayT == false);
    static_assert(CompoundT<int *>::IsFuncT == false);
    static_assert(CompoundT<int *>::IsMemPtrT == false);

    static_assert(CompoundT<int[3]>::IsPtrT == false);
    static_assert(CompoundT<int[3]>::IsRefT == false);
    static_assert(CompoundT<int[3]>::IsArrayT == true);
    static_assert(CompoundT<int[3]>::IsFuncT == false);
    static_assert(CompoundT<int[3]>::IsMemPtrT == false);

    static_assert(CompoundT<int[]>::IsPtrT == false);
    static_assert(CompoundT<int[]>::IsRefT == false);
    static_assert(CompoundT<int[]>::IsArrayT == true);
    static_assert(CompoundT<int[]>::IsFuncT == false);
    static_assert(CompoundT<int[]>::IsMemPtrT == false);

    static_assert(CompoundT<int Sample::*>::IsPtrT == false);
    static_assert(CompoundT<int Sample::*>::IsRefT == false);
    static_assert(CompoundT<int Sample::*>::IsArrayT == false);
    static_assert(CompoundT<int Sample::*>::IsFuncT == false);
    static_assert(CompoundT<int Sample::*>::IsMemPtrT == true);

    CompoundT<int Sample::*> c_sample;
    static_assert(c_sample.IsPtrT == false);
    static_assert(c_sample.IsRefT == false);
    static_assert(c_sample.IsArrayT == false);
    static_assert(c_sample.IsFuncT == false);
    static_assert(c_sample.IsMemPtrT == true);

    return 0;
}

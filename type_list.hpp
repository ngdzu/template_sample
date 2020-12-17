
#pragma once

#include <type_traits>
#include "type_utils.hpp"


template <typename T, typename U>
struct type_list
{
    using Head = T;
    using Tail = U;
};

template <typename T>
struct type_list<T, NullType>
{
    using Head = T;
    using Tail = NullType;
};

#define TYPE_LIST_1(T) \
    type_list<T, NullType>

#define TYPE_LIST_2(T1, T2) \
    type_list<T1, TYPE_LIST_1(T2)>

#define TYPE_LIST_3(T1, T2, T3) \
    type_list<T1, TYPE_LIST_2(T2, T3)>

#define TYPE_LIST_4(T1, T2, T3, T4) \
    type_list<T1, TYPE_LIST_3(T2, T3, T4)>

#define TYPE_LIST_5(T1, T2, T3, T4, T5) \
    type_list<T1, TYPE_LIST_4(T2, T3, T4, T5)>

// append
template <typename TL, typename T>
struct Append;

template <>
struct Append<NullType, NullType>
{
    using Result = NullType;
};

template<typename T>
struct Append<NullType, T>
{
    using Result = TYPE_LIST_1(T);
};

template <typename T, typename U>
struct Append<type_list<T, NullType>, U>
{
    using Result = TYPE_LIST_2(T, U);
};

template <typename T, typename U, typename X>
struct Append<type_list<T, U>, X>
{
    using Result = type_list<T, typename Append<U, X>::Result>;
};

// length
template <typename TL>
struct Length;

template <>
struct Length<NullType>
{
    enum
    {
        value = 0
    };
};

template <typename T>
struct Length<type_list<T, NullType>>
{
    enum
    {
        value = 1
    };
};

template <typename T, typename U>
struct Length<type_list<T, U>>
{
    enum
    {
        value = 1 + Length<U>::value
    };
};

// TypeAt
template <typename TL, int n>
struct TypeAt;

template <typename T, typename U>
struct TypeAt<type_list<T, U>, 0>
{
    using Result = T;
};

// Index out of bound, return NullType
// Alternatively, we can remove this specialization to force a compile error
template <int n>
struct TypeAt<NullType, n>
{
    using Result = NullType;
};

template <typename T, typename U, int n>
struct TypeAt<type_list<T, U>, n>
{
    using Result = typename TypeAt<U, n - 1>::Result;
};

// Index of 
template <typename TL, typename T>
struct IndexOf;


template <typename T>
struct IndexOf<NullType, T>
{
    enum {
        value = -1
    };
};

template <typename Tail, typename T>
struct IndexOf<type_list<T, Tail>, T>
{
    enum {
        value = 0
    };
};

template <typename Head,typename Tail, typename T>
struct IndexOf<type_list<Head, Tail>, T>
{
    enum {
        temp = IndexOf<Tail, T>::value,
        value = (temp == -1)? -1 : 1 + temp // if not found (-1), it is not found, don't add to the calculation
    };
};

template<typename TL, typename T>
struct Erase;

template<typename T>
struct Erase <NullType, T>
{
    using Result = NullType;
};

template<typename T>
struct Erase<type_list<T, NullType>, T>
{
    using Result = NullType;
};

template<typename T, typename U>
struct Erase<type_list<T, U>, T>
{
    using Result = T;
};

template<typename T, typename U, typename X>
struct Erase<type_list<T, U>, X>
{
    using Result = type_list<T, typename Erase<U, X>::Result>;
};

template<typename T>
struct NoDuplicates;

template<>
struct NoDuplicates<NullType>
{
    using Result = NullType;
};

template<typename Head, typename Tail>
struct NoDuplicates<type_list<Head, Tail>>
{
private: 
    using T1 = typename NoDuplicates<Tail>::Result;
    using T2 = typename Erase<T1, Head>::Result;
public:
    using Result = type_list<Head, T2>;
};

template<typename TL, typename t, typename U>
struct Replace;

template<typename T, typename U>
struct Replace<NullType, T, U>
{
    using Result = NullType;
};

template<typename Head, typename Tail, typename U>
struct Replace<type_list<Head, Tail>, Head, U>
{
    using Result = type_list<U, Tail>;
};

template<typename Head, typename Tail, typename T, typename U>
struct Replace<type_list<Head, Tail>, T, U>
{
    using Result = type_list<Head, typename Replace<Tail, T, U>::Result>;
};







#pragma once

struct NullType;

template <int N>
struct Int2Type
{
    enum {
        value = N
    };
};

template <typename T>
struct Type2Type
{
    using OriginalType = T;
};



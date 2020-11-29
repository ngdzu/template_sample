#include "type_list.hpp"

template <typename TL, template<class> typename Unit>
struct GenScatterHierarchy;

template <typename Atomic, template<class> typename Unit >
struct GenScatterHierarchy : public Unit<Atomic>
{
};

template <typename T1, typename T2, template<class> typename Unit>
struct GenScatterHierarchy <type_list<T1, T2>, Unit>
    : public GenScatterHierarchy<T1, Unit>
    , public GenScatterHierarchy<T2, Unit>
{
};

template <template<class> typename Unit>
struct GenScatterHierarchy <NullType, Unit>
{
};


template <typename T, typename TL, template<class> typename Unit>
Unit<T>&
Field(GenScatterHierarchy<TL, Unit>& obj)
{
    return obj;
}


template<int i, typename TL, template<class> typename Unit>
Unit<typename TypeAt<TL,i>::Result>&
// auto &
Field(GenScatterHierarchy<TL, Unit>& obj)
{
    if constexpr (i == 0)
    {
        Field<typename TL::Head>& temp = obj;
        return temp;
    }
    else
    {
        auto& temp = Field<i-1>(obj);
        return temp;
    }
}


